using SocialGameBLL.Entities;
using SocialGameBLL.Service;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace SocialGameBLL.Controllers
{
    struct Node
    {
        public UserEntity User { get; set; }
        public int Level { get; set; }

        public override bool Equals(object obj)
        {
            if(obj is Node)
            {
                Node Other = (Node)obj;
                return this.User.Equals(Other.User);
            }
            return false;
        }
    }

    public class RelationshipsController
    {
        SocialGameBLLDbContext db = new SocialGameBLLDbContext();

        public ICollection<RelationshipTag> GetRelationshipTags()
        {            
            ICollection<RelationTagEntity> RelationTagEntities = db.RelationTags.ToList();

            ICollection<RelationshipTag> RelationshipTags = ConvertRelationTagEntitiesToRelationshipTag(RelationTagEntities);
            return RelationshipTags;
        }

        public Graph GetRelationships(User User, int Depth)
        {
            Node FirstNode = new Node
            {
                User = db.Users.Find(User.Email),
                Level = 0
            };

            IList<Node> ListOfNodes = new List<Node>();
            IList<RelationshipEntity> ListOfArcs = new List<RelationshipEntity>();
            IList<InterestEntity> Interests = new List<InterestEntity>();
            IList<RelationTagEntity> RelationTags = new List<RelationTagEntity>();
            IList<HumourStatusEntity> HumourStatus = new List<HumourStatusEntity>();
            ListOfNodes.Add(FirstNode);

            GetRelatedUsers(0, ListOfNodes, ListOfArcs, Interests, RelationTags, HumourStatus, Depth);

            return new Graph
            {
                Users = ConvertNodeToUser(ListOfNodes),
                Relationships = ConvertRelationshipEntitiesToRelationships(ListOfArcs),
                Interests = ConvertToInterestFromInterestEntities(Interests),
                RelationshipTags = ConvertToRelationshipTagsFromRelationTagEntities(RelationTags),
                HumourStatus = ConvertToHumourStatusFromHumourStatusEntities(HumourStatus)
            };
        }

        private void GetRelatedUsers(int Position, IList<Node> Nodes, IList<RelationshipEntity> Relationships
                                     , IList<InterestEntity> Interests, IList<RelationTagEntity> RelationTags
                                     , IList<HumourStatusEntity> HumourStatus, int Depth)
        {
            if (Nodes.Count <= Position || Nodes[Position].Level >= Depth)
                return;

            UserEntity CurrentNodeUser = Nodes[Position].User;
            foreach(InterestEntity InterestEntity in CurrentNodeUser.Interests)
            {
                if(!Interests.Contains(InterestEntity))
                {
                    Interests.Add(InterestEntity);
                }
            }

            if (!HumourStatus.Contains(CurrentNodeUser.HumourStatus))
            {
                HumourStatus.Add(CurrentNodeUser.HumourStatus);
            }

            ICollection<RelationshipEntity> UserRelationships = CurrentNodeUser.GetAllUsersRelationships();
            foreach (RelationshipEntity Relationship in UserRelationships)
            {
                if (!Relationships.Contains(Relationship))
                {
                    Relationships.Add(Relationship);
                    if(!RelationTags.Contains(Relationship.RelationTag))
                    {
                        RelationTags.Add(Relationship.RelationTag);
                    }
                    Node User = new Node
                    {
                        User = Relationship.User,
                        Level = 1 + Nodes[Position].Level
                    };

                    Node Friend = new Node
                    {
                        User = Relationship.Friend,
                        Level = 1 + Nodes[Position].Level
                    };
                    if (!Nodes.Contains(User))
                    {
                        Nodes.Add(User);
                    }
                    if (!Nodes.Contains(Friend))
                    {
                        Nodes.Add(Friend);
                    }
                }
            }

            GetRelatedUsers(++Position, Nodes, Relationships, Interests, RelationTags, HumourStatus, Depth);

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

        private ICollection<User> ConvertNodeToUser(IList<Node> Nodes)
        {
            ICollection<User> Users = new List<User>();
            foreach (Node Node in Nodes)
            {
                UserEntity UserEntity = Node.User;
                Users.Add(new User
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

        private ICollection<int> GetInterestsIdsFromInterests(ICollection<InterestEntity> Interests)
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

        private ICollection<RelationshipTag> ConvertToRelationshipTagsFromRelationTagEntities(ICollection<RelationTagEntity> RelationTagEntities)
        {
            ICollection<RelationshipTag> RelationshipTags = new List<RelationshipTag>();
            foreach (RelationTagEntity RelationTagEntity in RelationTagEntities)
            {
                RelationshipTags.Add(new RelationshipTag
                {
                    Id = RelationTagEntity.ID,
                    Name = RelationTagEntity.Name
                });
            }
            return RelationshipTags;
        }

        private ICollection<Interest> ConvertToInterestFromInterestEntities(ICollection<InterestEntity> InterestEntities)
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

        private ICollection<HumourStatus> ConvertToHumourStatusFromHumourStatusEntities(ICollection<HumourStatusEntity> HumourStatusEntities)
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
    }
}