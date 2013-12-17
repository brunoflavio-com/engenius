using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace SocialGamePublicAPI.Service
{
    public class ServiceConverter
    {

         public static Graph convertGraph(SocialGameBLLService.Graph BLLGraph)
        {
            List<User> users = new List<User>();
            foreach(SocialGameBLLService.User BLLUser in BLLGraph.Users)
            {
                User User = convertUser(BLLUser);
                users.Add(User);
            };

            List<Relationship> relationships = new List<Relationship>();
            foreach (SocialGameBLLService.Relationship BLLRelationship in BLLGraph.Relationships)
            {
                Relationship Relationship = convertRelationship(BLLRelationship);
                relationships.Add(Relationship);
            };

            List<RelationshipTag> relationshipsTags = new List<RelationshipTag>();
            
            foreach (SocialGameBLLService.RelationshipTag BLLRelationshipTag in BLLGraph.RelationshipTags)
            {
                Service.RelationshipTag RelationshipTag = convertRelationshipTag(BLLRelationshipTag);
                relationshipsTags.Add(RelationshipTag);
            };

            List<Interest> interests = new List<Interest>();

            foreach (SocialGameBLLService.Interest BLLInterest in BLLGraph.Interests)
            {
                Service.Interest Interest = convertInterest(BLLInterest);
                interests.Add(Interest);
            };

            List<HumourStatus> humorStatusList = new List<HumourStatus>();

            foreach (SocialGameBLLService.HumourStatus BLLHumorStatus in BLLGraph.HumourStatus)
            {
                Service.HumourStatus HumorStatus = convertHumorStatus(BLLHumorStatus);
                humorStatusList.Add(HumorStatus);
            };

                Graph Graph = new Graph
            {
                Users = users,
                Relationships = relationships,
                RelationshipTags = relationshipsTags,
                Interests = interests,
                HumourStatus = humorStatusList
            };

            return Graph;
        }
        public static User convertUser(SocialGameBLLService.User BLLUser)
        {

            User User = new User
            {
                Email = BLLUser.Email,
                HumourStatusId = BLLUser.HumourStatusId,
                InterestsIDs = BLLUser.InterestsIDs,
                Name = BLLUser.Name,
                Surname = BLLUser.Surname
            };

            return User;
        }

        public static HumourStatus convertHumorStatus(SocialGameBLLService.HumourStatus BLLHumorStatus)
        {
           return new HumourStatus{
           Id = BLLHumorStatus.Id,
            Name = BLLHumorStatus.Name
           };
        }

        public static Interest convertInterest(SocialGameBLLService.Interest BLLInterest)
        {
            return new Interest
            {
                Id = BLLInterest.Id,
                Name = BLLInterest.Name
            };
        }

        public static Relationship convertRelationship(SocialGameBLLService.Relationship BLLRelationship)
        {
            return new Relationship
            {
                RelationshipTagId = BLLRelationship.RelationshipTagId,
                Strength = BLLRelationship.Strength,
                UserAEmail = BLLRelationship.UserAEmail,
                UserBEmail = BLLRelationship.UserBEmail
            };
        }

        public static RelationshipTag convertRelationshipTag(SocialGameBLLService.RelationshipTag BLLRelationshipTag)
        {
            return new RelationshipTag
            {
                Id = BLLRelationshipTag.Id,
                Name = BLLRelationshipTag.Name
            };
        }
    }


}