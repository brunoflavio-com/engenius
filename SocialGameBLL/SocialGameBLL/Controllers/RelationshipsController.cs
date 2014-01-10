using Newtonsoft.Json;
using SocialGameBLL.Entities;
using SocialGameBLL.Service;
using SocialGameBLL.Util;
using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Configuration;
using System.IO;
using System.Linq;
using System.Net;
using System.Text;
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

        public RelationshipTag GetRelationshipTag(int Id)
        {
            try
            {
                RelationTagEntity RTEntity = db.RelationTags.Find(Id);
                return EntityServiceConverter.ConvertRelationTagEntityToRelationTag(RTEntity);
            }catch(Exception e)
            {
                throw new Exception(e.Message, e);
            }
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
                RelationshipTags = EntityServiceConverter.ConvertRelationTagEntitiesToRelationshipTag(RelationTags),
                HumourStatus = EntityServiceConverter.ConvertToHumourStatusFromHumourStatusEntities(HumourStatus)
            };
        }

        public Relationship GetRelationship(User Me, User Other)
        {
            try
            {
                UserEntity MyEntity = db.Users.Find(Me.Email);
                UserEntity OtherEntity = db.Users.Find(Other.Email);
                RelationshipEntity RelationshipEntity;
                try
                {
                    RelationshipEntity = MyEntity.GetAllUsersRelationships().Single(r => (r.UserEmail == MyEntity.Email && r.FriendEmail == OtherEntity.Email) || (r.FriendEmail == MyEntity.Email && r.UserEmail == OtherEntity.Email));
                }catch(Exception e)
                {
                    return null;
                }
                return EntityServiceConverter.ConvertRelationshipEntityToRelationship(RelationshipEntity);
            }catch(Exception e)
            {
                throw new Exception(e.Message, e);
            }
        }

        public void DeleteRelationship(User Me, User Other)
        {
            try
            {
                UserEntity MyEntity = db.Users.Find(Me.Email);
                UserEntity OtherEntity = db.Users.Find(Other.Email);

                RelationshipEntity RelationshipEntity = MyEntity.GetAllUsersRelationships().Single(r => (r.UserEmail == MyEntity.Email && r.FriendEmail == OtherEntity.Email) || (r.FriendEmail == MyEntity.Email && r.UserEmail == OtherEntity.Email));

                db.Relationships.Remove(RelationshipEntity);
                db.SaveChanges();
            }catch(Exception e)
            {
                throw new Exception(e.Message, e);
            }
        }

        public RelationshipRequest MakeRelationshipRequest(User Me, User Other, int RelationshipTagId, int Strength)
        {
            try
            {
                UserEntity MyEntity = db.Users.Find(Me.Email);
                UserEntity OtherEntity = db.Users.Find(Other.Email);
                RelationTagEntity TagEntity = db.RelationTags.Find(RelationshipTagId);

                RelationshipRequestEntity RelationshipRequestEntity = db.RelationshipsRequests.Find(MyEntity.Email, OtherEntity.Email);

                if (RelationshipRequestEntity != null)
                {
                    RelationshipRequestEntity.RelationTagID = TagEntity.ID;
                    RelationshipRequestEntity.Strength = Strength;
                }
                else
                {
                    RelationshipRequestEntity = new RelationshipRequestEntity();

                    RelationshipRequestEntity.UserEmail = MyEntity.Email;
                    RelationshipRequestEntity.FriendEmail = OtherEntity.Email;
                    RelationshipRequestEntity.RelationTagID = TagEntity.ID;
                    RelationshipRequestEntity.Strength = Strength;

                    db.RelationshipsRequests.Add(RelationshipRequestEntity);
                }
                db.SaveChanges();
                return EntityServiceConverter.ConvertRelationshipRequestEntityToRelationshipRequest(RelationshipRequestEntity);
            }catch (Exception e)
            {
                throw new Exception(e.Message, e);
            }
        }

        public void AcceptRelationshipRequest(User Me, User Other)
        {
            try
            {
                UserEntity MyEntity = db.Users.Find(Me.Email);
                UserEntity OtherEntity = db.Users.Find(Other.Email);

                RelationshipEntity RelationshipEntity;
                RelationshipRequestEntity RelationshipRequestEntity = db.RelationshipsRequests.Find(OtherEntity.Email, MyEntity.Email);
                try
                {
                    RelationshipEntity = MyEntity.GetAllUsersRelationships().Single(r => (r.UserEmail == MyEntity.Email && r.FriendEmail == OtherEntity.Email) || (r.FriendEmail == MyEntity.Email && r.UserEmail == OtherEntity.Email));
                }
                catch (Exception e)
                {
                    RelationshipEntity = null;
                }


                if(RelationshipEntity != null)
                {
                    RelationshipEntity.Strength = RelationshipRequestEntity.Strength;
                    RelationshipEntity.RelationTagID = RelationshipRequestEntity.RelationTagID;
                }
                else
                {
                    RelationshipEntity = new RelationshipEntity();

                    RelationshipEntity.FriendEmail = MyEntity.Email;
                    RelationshipEntity.UserEmail = OtherEntity.Email;
                    RelationshipEntity.Strength = RelationshipRequestEntity.Strength;
                    RelationshipEntity.RelationTagID = RelationshipRequestEntity.RelationTagID;
                    db.Relationships.Add(RelationshipEntity);
                }

                db.RelationshipsRequests.Remove(RelationshipRequestEntity);
                db.SaveChanges();

            }catch(Exception e)
            {
                throw new Exception(e.Message, e);
            }
        }

        public void RejectRelationshipRequest(User Me, User Other)
        {
            try
            {
                UserEntity MyEntity = db.Users.Find(Me.Email);
                UserEntity OtherEntity = db.Users.Find(Other.Email);
                RelationshipRequestEntity RelationshipRequestEntity = db.RelationshipsRequests.Find(OtherEntity.Email, MyEntity.Email);
                db.RelationshipsRequests.Remove(RelationshipRequestEntity);
                db.SaveChanges();
            }catch(Exception e)
            {
                throw new Exception(e.Message, e);
            }
        }

        public RelationshipRequest GetPendingRequest(User Me, User Other)
        {
            try
            {
                RelationshipRequestEntity RelationshipRequestEntity = db.RelationshipsRequests.Find(Me.Email, Other.Email);
                if (RelationshipRequestEntity == null)
                    return null;

                return EntityServiceConverter.ConvertRelationshipRequestEntityToRelationshipRequest(RelationshipRequestEntity);
            }catch(Exception e)
            {
                throw new Exception(e.Message, e);
            }
        }

        public ICollection<RelationshipRequest> GetUserPendingRequests(User Me)
        {
            try
            {
                UserEntity MyEntity = db.Users.Find(Me.Email);
                ICollection<RelationshipRequestEntity> RelationshipRequestEntities = db.RelationshipsRequests.Where(rr => rr.UserEmail == MyEntity.Email).ToList();
                if (RelationshipRequestEntities == null)
                {
                    return null;
                }
                return EntityServiceConverter.ConvertRelationshipRequestEntitiesToRelationshipRequests(RelationshipRequestEntities);
            }catch(Exception e)
            {
                throw new Exception(e.Message, e);
            }
        }

        public ICollection<RelationshipRequest> GetPendingRequestsToUser(User Me)
        {
            try
            {
                UserEntity MyEntity = db.Users.Find(Me.Email);
                ICollection<RelationshipRequestEntity> RelationshipRequestEntities = db.RelationshipsRequests.Where(rr => rr.FriendEmail == MyEntity.Email).ToList();
                if (RelationshipRequestEntities == null)
                {
                    return null;
                }
                return EntityServiceConverter.ConvertRelationshipRequestEntitiesToRelationshipRequests(RelationshipRequestEntities);
            }
            catch (Exception e)
            {
                throw new Exception(e.Message, e);
            }
        }

        public ICollection<User> GetShortestPath(User Me, User Goal, int Depth)
        {
            /*Load Graph on to server*/
            Graph Graph = GetRelationships(Me, Depth);
            string JsonGraph = JsonConvert.SerializeObject(Graph, Formatting.Indented);
            string AIServiceUrl = ConfigurationManager.AppSettings["SocialGameAIUrl"];

            CookieContainer CookieJar = new CookieContainer();
            string PostResponse = PrologRequest.MakeJsonPostRequest(PrologRequest.LOAD_USER_GRAPH, JsonGraph, CookieJar);

            /*Ask Server For Shortest Path*/
            OrderedDictionary Params = new OrderedDictionary();
            Params["origin"] = Me.Email;
            Params["destination"] = Goal.Email;
            string GetResponse = PrologRequest.MakeJsonGetResquest(PrologRequest.GET_SHORTEST_PATH, Params, CookieJar);

            return null;
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