using SocialGameWebsite.SocialGameBLLService;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using SocialGameWebsite.Models;

namespace SocialGameWebsite.Controllers
{
    public class LeaderboardController : Controller
    {

        SocialGameBLLServiceClient Proxy = new SocialGameBLLServiceClient();
        //
        // GET: /Leaderboard/

        public ActionResult Index()
        {
            return View();
        }

        public ActionResult NormalModeTop10(int Page=1)
        {
            ICollection<UserScore> ServiceScores = Proxy.GetPaginatedUsersScores(10 , Page);
            NormalModePointsLeaderBoardViewModel Top10ViewModel = new NormalModePointsLeaderBoardViewModel();

            Top10ViewModel.IsInTopTen = false;

            foreach(UserScore Score in ServiceScores)
            {
                UserScoreViewModel ScoreVM = new UserScoreViewModel
                {
                    Position = Score.Position,
                    UserEmail = Score.UserEmail,
                    UserName = Score.UserName,
                    UserSurname = Score.UserSurname,
                    UserLevel = Score.UserLevel,
                    UserPoints = Score.UserPoints
                };

                if (Score.UserEmail == User.Identity.Name)
                {
                    Top10ViewModel.IsInTopTen = true;
                    Top10ViewModel.HasScore = true;
                    Top10ViewModel.MyScore = ScoreVM;
                }

                Top10ViewModel.Scores.Add(ScoreVM);
            }

            if (!Top10ViewModel.IsInTopTen)
            {
                UserScore MyScore = Proxy.GetUserScore(new User { Email = User.Identity.Name });
                if (MyScore != null)
                {
                    Top10ViewModel.HasScore = true;
                    Top10ViewModel.MyScore = new UserScoreViewModel 
                    {
                        Position = MyScore.Position,
                        UserEmail = MyScore.UserEmail,
                        UserName = MyScore.UserName,
                        UserSurname = MyScore.UserSurname,
                        UserLevel = MyScore.UserLevel,
                        UserPoints = MyScore.UserPoints
                    };
                }
                else
                {
                    Top10ViewModel.HasScore = false;
                }

            }

            return PartialView(Top10ViewModel);
        }

        public ActionResult Top10UserNetworkSizeLeaderboard()
        {
            ICollection<UserNetworkSizeScore> ServiceScores = Proxy.GetPaginatedUsersNetworkSizeScores(10, 1);
            Top10UserNetworkSizeLeaderBoardViewModel Top10ViewModel = new Top10UserNetworkSizeLeaderBoardViewModel();

            Top10ViewModel.IsInTopTen = false;

            foreach (UserNetworkSizeScore Score in ServiceScores)
            {
                UserNetworkSizeScoreViewModel ScoreVM = new UserNetworkSizeScoreViewModel
                {
                    Position = Score.Position,
                    UserEmail = Score.UserEmail,
                    UserName = Score.UserName,
                    UserSurname = Score.UserSurname,
                    UserNetworkSize = Score.UserNetworkSize
                };

                if (ScoreVM.UserEmail == User.Identity.Name)
                {
                    Top10ViewModel.IsInTopTen = true;
                    Top10ViewModel.HasScore = true;
                    Top10ViewModel.MyScore = ScoreVM;
                }

                Top10ViewModel.Scores.Add(ScoreVM);
            }

            if (!Top10ViewModel.IsInTopTen)
            {
                UserNetworkSizeScore MyScore = Proxy.GetUserNetworkSizeScore(new User { Email = User.Identity.Name });
                if (MyScore != null)
                {
                    Top10ViewModel.HasScore = true;
                    Top10ViewModel.MyScore = new UserNetworkSizeScoreViewModel
                    {
                        Position = MyScore.Position,
                        UserEmail = MyScore.UserEmail,
                        UserName = MyScore.UserName,
                        UserSurname = MyScore.UserSurname,
                        UserNetworkSize = MyScore.UserNetworkSize
                    };
                }
                else
                {
                    Top10ViewModel.HasScore = false;
                }

            }

            return PartialView(Top10ViewModel);
        }

        public ActionResult Top10UserNetworkStrengthLeaderboard()
        {
            ICollection<UserNetworkStrengthScore> ServiceScores = Proxy.GetPaginatedUsersNetworkStrengthScores(10, 1);
            Top10UserNetworkStrongestLeaderBoardViewModel Top10ViewModel = new Top10UserNetworkStrongestLeaderBoardViewModel();

            Top10ViewModel.IsInTopTen = false;

            foreach (UserNetworkStrengthScore Score in ServiceScores)
            {
                UserNetworkStrengthScoreViewModel ScoreVM = new UserNetworkStrengthScoreViewModel
                {
                    Position = Score.Position,
                    UserEmail = Score.UserEmail,
                    UserName = Score.UserName,
                    UserSurname = Score.UserSurname,
                    UserNetworkAverageStrength = Score.UserNetworkStrength
                };

                if (ScoreVM.UserEmail == User.Identity.Name)
                {
                    Top10ViewModel.IsInTopTen = true;
                    Top10ViewModel.HasScore = true;
                    Top10ViewModel.MyScore = ScoreVM;
                }

                Top10ViewModel.Scores.Add(ScoreVM);
            }

            if (!Top10ViewModel.IsInTopTen)
            {
                UserNetworkSizeScore MyScore = Proxy.GetUserNetworkSizeScore(new User { Email = User.Identity.Name });
                if (MyScore != null)
                {
                    Top10ViewModel.HasScore = true;
                    Top10ViewModel.MyScore = new UserNetworkStrengthScoreViewModel
                    {
                        Position = MyScore.Position,
                        UserEmail = MyScore.UserEmail,
                        UserName = MyScore.UserName,
                        UserSurname = MyScore.UserSurname,
                        UserNetworkAverageStrength = MyScore.UserNetworkSize
                    };
                }
                else
                {
                    Top10ViewModel.HasScore = false;
                }

            }

            return PartialView(Top10ViewModel);
        }
    }
}
