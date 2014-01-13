using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;

namespace SocialGameWebsite.Models
{
    public class StatisticsViewModel
    {
        public string Title { get; set; }
        public int UserCount { get; set; }
        public double RelationshipStrenghtAverage { get; set; }
    }

    public class TagCloudViewModel
    {
        public string Title { get; set;}
        
        public Dictionary<string, int> Data {get;set;}

        public TagCloudViewModel()
        {
            Data = new Dictionary<string,int>();
        }

    }

    public class UserScoreViewModel
    {
        public int Position { get; set; }
        public string UserEmail { get; set; }
        public string UserName { get; set; }
        public string UserSurname { get; set; }
        public int UserLevel { get; set; }
        public float UserPoints { get; set; }
    }

    public class NormalModePointsLeaderBoardViewModel
    {
        public NormalModePointsLeaderBoardViewModel()
        {
            Scores = new List<UserScoreViewModel>();
        }
        public ICollection<UserScoreViewModel> Scores { get; set; }

        public bool HasScore{get; set;}
        public bool IsInTopTen { get; set; }
        public UserScoreViewModel MyScore{get;set;}
    }
}