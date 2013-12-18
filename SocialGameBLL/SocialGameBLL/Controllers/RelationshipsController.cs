using SocialGameBLL.Entities;
using SocialGameBLL.Service;
using SocialGameBLL.Util;
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

            ICollection<RelationshipTag> RelationshipTags = EntityServiceConverter.ConvertRelationTagEntitiesToRelationshipTag(RelationTagEntities);
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
                Relationships = EntityServiceConverter.ConvertRelationshipEntitiesToRelationships(ListOfArcs),
                Interests = EntityServiceConverter.ConvertToInterestFromInterestEntities(Interests),
                RelationshipTags = EntityServiceConverter.ConvertToRelationshipTagsFromRelationTagEntities(RelationTags),
                HumourStatus = EntityServiceConverter.ConvertToHumourStatusFromHumourStatusEntities(HumourStatus)
            };
        }

        public RelationshipRequest MakeRelationshipRequest(User Me, User Other, int RelationshipTagId, int Strength)
        {
            try
            {
                UserEntity MyEntity = db.Users.Find(Me.Email);
                UserEntity OtherEntity = db.Users.Find(Other.Email);
                RelationTagEntity TagEntity = db.RelationTags.Find(RelationshipTagId);
                db.RelationshipsRequests.Add(new RelationshipRequestEntity
                    {
                        UserEmail = MyEntity.Email,
                        FriendEmail = OtherEntity.Email,
                        RelationTagID = TagEntity.ID,
                        Strength = Strength
                    });
                db.SaveChanges();
                RelationshipRequestEntity RequestEntityCreated = db.RelationshipsRequests.Find(MyEntity.Email, OtherEntity.Email);
                return EntityServiceConverter.ConvertToRelationshipRequestFromRelationshipRequestEntity(RequestEntityCreated);
            }
            catch (Exception e)
            {
                throw new Exception(e.Message);
            }
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
                     InterestsIDs = EntityServiceConverter.GetInterestsIdsFromInterests(UserEntity.Interests),
                     FacebookProfile = UserEntity.FacebookProfile,
                     LinkedInProfile = UserEntity.LinkedInProfile,
                     PhoneNumber = UserEntity.PhoneNumber
                });
            }
            return Users;
        }
    }
}