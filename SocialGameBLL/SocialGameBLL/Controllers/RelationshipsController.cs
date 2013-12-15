using SocialGameBLL.Entities;
using SocialGameBLL.Service;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace SocialGameBLL.Controllers
{
    public class RelationshipsController
    {
        SocialGameBLLDbContext db = new SocialGameBLLDbContext();

        public ICollection<RelationshipTag> GetRelationshipTags()
        {            
            ICollection<RelationTagEntity> RelationTagEntities = db.RelationTags.ToList();

            ICollection<RelationshipTag> RelationshipTags = ConvertRelationTagEntitiesToRelationshipTag(RelationTagEntities);
            return RelationshipTags;
        }

        public Graph GetRalationships(User User)
        {
            UserEntity FirstNode = db.Users.Find(User.Email);
            IList<UserEntity> ListOfNodes = new List<UserEntity>();
            IList<RelationshipEntity> ListOfArcs = new List<RelationshipEntity>();
            ListOfNodes.Add(FirstNode);

            GetRelatedUsers(0, ListOfNodes, ListOfArcs);

            ICollection<User> Users = ConvertUserEntitiesToUser(ListOfNodes);
            ICollection<Relationship> Relationships = ConvertRelationshipEntitiesToRelationships(ListOfArcs);

            return new Graph
            {
                Users = Users,
                Relationships = Relationships
            };
        }

        private void GetRelatedUsers(int Position, IList<UserEntity> Users, IList<RelationshipEntity> Relationships)
        {
            if (Users.Count <= Position)
                return;

            UserEntity CurrentNode = Users[Position];
            ICollection<RelationshipEntity> UserRelationships = CurrentNode.GetAllUsersRelationships();
            foreach (RelationshipEntity Relationship in UserRelationships)
            {
                if (!Relationships.Contains(Relationship))
                {
                    Relationships.Add(Relationship);
                    if (!Users.Contains(Relationship.User)) Users.Add(Relationship.User);
                    if (!Users.Contains(Relationship.Friend)) Users.Add(Relationship.Friend);
                }
            }

            GetRelatedUsers(++Position, Users, Relationships);

        }

        private ICollection<RelationshipTag> ConvertRelationTagEntitiesToRelationshipTag(ICollection<RelationTagEntity> Entities)
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

        private ICollection<User> ConvertUserEntitiesToUser(IList<UserEntity> UserEntities)
        {
            ICollection<User> Users = new List<User>();
            foreach (UserEntity UserEntity in UserEntities)
            {
                Users.Add(new User
                {
                     Email = UserEntity.Email,
                     Name = UserEntity.Name,
                     Surname = UserEntity.Surname,
                     Birthdate = (UserEntity.Birthdate != null) ? (DateTime)UserEntity.Birthdate : DateTime.MinValue,
                     FacebookProfile = UserEntity.FacebookProfile,
                     LinkedInProfile = UserEntity.LinkedInProfile,
                     PhoneNumber = UserEntity.PhoneNumber
                });
            }
            return Users;
        }

        private ICollection<Relationship> ConvertRelationshipEntitiesToRelationships(IList<RelationshipEntity> RelationshipEntities)
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
    }
}