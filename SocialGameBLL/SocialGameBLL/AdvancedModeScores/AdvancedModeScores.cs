using SocialGameBLL.Controllers;
using SocialGameBLL.Entities;
using SocialGameBLL.Service;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;
using System.Web;

namespace SocialGameBLL.AdvancedModeScores
{
    public class AdvancedModeScoresSingleton
    {
        private const int UPDATE_INTERVAL_IN_MINUTES = 10; 
        private static readonly object SyncLock = new object();
        private static AdvancedModeScoresSingleton Instance = null;

        private DateTime LastUpDated;

        private IList<NetworkSizeScore> SizeScores;
        private IList<NetworkStrengthScore> StrengthScores;

        /*Singleton*/
        private AdvancedModeScoresSingleton() 
        {
            SizeScores = new List<NetworkSizeScore>();
            StrengthScores = new List<NetworkStrengthScore>();
            /*Ao ser criado vai buscar os dados pela 1ª vez*/
            CalculateStats();
        }

        public static AdvancedModeScoresSingleton GetInstance() 
        {
            if (Instance == null)
            {
                Instance = new AdvancedModeScoresSingleton();
            }
            return Instance;
        }

        public IList<NetworkSizeScore> GetSizeScores()
        {
            /*Se a ultima vez que os dados foram calculados foi há mais de 10 min volta a manda calcular em back ground e devolve os actuais*/
            DateTime now = DateTime.Now;
            if(now.Subtract(LastUpDated).TotalMinutes > UPDATE_INTERVAL_IN_MINUTES)
            {
                CalculateStatsAsync();
            }
            lock (SyncLock)
            {
                return new List<NetworkSizeScore>(SizeScores);
            }
        }

        public IList<NetworkStrengthScore> GetStrengthScores()
        {
            /*Se a ultima vez que os dados foram calculados foi há mais de 10 min volta a manda calcular em back ground e devolve os actuais*/
            DateTime now = DateTime.Now;
            if (now.Subtract(LastUpDated).TotalMinutes > UPDATE_INTERVAL_IN_MINUTES)
            {
                CalculateStatsAsync();
            }
            lock (SyncLock)
            {
                return new List<NetworkStrengthScore>(StrengthScores);
            }
        }

        private void CalculateStatsAsync()
        {
            Thread CalculateThread = new Thread(CalculateStats);
            CalculateThread.Start();
        }

        private void CalculateStats()
        {
            LastUpDated = DateTime.Now;
            IList<NetworkSizeScore> TempSizeScores =  new List<NetworkSizeScore>();
            IList<NetworkStrengthScore> TempStrengthScores = new List<NetworkStrengthScore>();

            SocialGameBLLDbContext db = new SocialGameBLLDbContext();
            UsersController Controller = new UsersController();

            ICollection<UserEntity> Users = db.Users.ToList();

            foreach (UserEntity User in Users)
            {
                NetworkStatistics UserStats = Controller.GetGraphStats(new User { Email = User.Email});
                TempSizeScores.Add(new NetworkSizeScore 
                {
                    UserEmail = User.Email,
                    NetworkSize = UserStats.UserCount
                });
                TempStrengthScores.Add(new NetworkStrengthScore
                {
                    UserEmail = User.Email,
                    AvarageStregth = UserStats.RelationshipStrenghtAverage
                });
            }

            lock (SyncLock)
            {
                SizeScores = TempSizeScores;
                StrengthScores = TempStrengthScores;
            }
        }
    }
}