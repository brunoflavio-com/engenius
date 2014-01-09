using SocialGameBLL.Entities;
using SocialGameBLL.Service;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace SocialGameBLL.Util
{
    public static class EntityServiceConverter
    {
        public static ICollection<RelationshipTag> ConvertRelationTagEntitiesToRelationshipTag(ICollection<RelationTagEntity> Entities)
        {
            ICollection<RelationshipTag> RelationshipTags = new List<RelationshipTag>();
            foreach (RelationTagEntity Entity in Entities)
            {
                RelationshipTags.Add(new RelationshipTag
                {
                    Id = Entity.ID,
                    Name = Entity.Name
                });
            }
            return RelationshipTags;
        }

        public static RelationshipTag ConvertRelationTagEntityToRelationTag(RelationTagEntity RelationTagEntity)
        {
            return new RelationshipTag
                {
                    Id = RelationTagEntity.ID,
                    Name = RelationTagEntity.Name
                };
        }

        public static ICollection<Relationship> ConvertRelationshipEntitiesToRelationships(IList<RelationshipEntity> RelationshipEntities)
        {
            ICollection<Relationship> Relationships = new List<Relationship>();
            foreach (RelationshipEntity RelationshipEntity in RelationshipEntities)
            {
                Relationships.Add(new Relationship
                {
                    UserAEmail = RelationshipEntity.UserEmail,
                    UserBEmail = RelationshipEntity.FriendEmail,
                    Strength = RelationshipEntity.Strength,
                    RelationshipTagId = RelationshipEntity.RelationTagID
                });
            }
            return Relationships;
        }

        public static ICollection<Interest> ConvertToInterestFromInterestEntities(ICollection<InterestEntity> InterestEntities)
        {
            ICollection<Interest> Interests = new List<Interest>();
            foreach (InterestEntity InterestEntity in InterestEntities)
            {
                Interests.Add(new Interest
                {
                    Id = InterestEntity.ID,
                    Name = InterestEntity.Name
                });
            }
            return Interests;
        }

        public static ICollection<HumourStatus> ConvertToHumourStatusFromHumourStatusEntities(ICollection<HumourStatusEntity> HumourStatusEntities)
        {
            ICollection<HumourStatus> HumourStatus = new List<HumourStatus>();
            foreach (HumourStatusEntity HumourStatusEntity in HumourStatusEntities)
            {
                HumourStatus.Add(new HumourStatus
                {
                    Id = HumourStatusEntity.ID,
                    Name = HumourStatusEntity.Name
                });
            }
            return HumourStatus;
        }

        public static HumourStatus ConvertToHumourStatusFromHumourStatusEntity(HumourStatusEntity HumourStatusEntity)
        {
            return new HumourStatus
            {
                Id = HumourStatusEntity.ID,
                Name = HumourStatusEntity.Name
            };
        }

        public static User ConvertUserEntityToUser(UserEntity UserEntity)
        {
            return new User
            {
                Email = UserEntity.Email,
                Name = UserEntity.Name,
                Surname = UserEntity.Surname,
                Birthdate = (UserEntity.Birthdate != null) ? (DateTime)UserEntity.Birthdate : DateTime.MinValue,
                HumourStatusId = UserEntity.HumourStatusID,
                InterestsIDs = GetInterestsIdsFromInterests(UserEntity.Interests),
                FacebookProfile = UserEntity.FacebookProfile,
                LinkedInProfile = UserEntity.LinkedInProfile,
                PhoneNumber = UserEntity.PhoneNumber
            };
        }

        public static ICollection<int> GetInterestsIdsFromInterests(ICollection<InterestEntity> Interests)
        {
            ICollection<int> InterestsIDs = new List<int>();
            if (Interests != null)
            {
                foreach (InterestEntity Interest in Interests)
                {
                    InterestsIDs.Add(Interest.ID);
                }
            }
            return InterestsIDs;
        }

        public static RelationshipRequest ConvertToRelationshipRequestFromRelationshipRequestEntity(RelationshipRequestEntity RequestEntity)
        {
            return new RelationshipRequest 
            { 
                RequesterEmail = RequestEntity.UserEmail,
                RequestedEmail = RequestEntity.FriendEmail,
                RelationshipTagId = RequestEntity.RelationTagID,
                Strength = RequestEntity.Strength
            };
        }
    }
}