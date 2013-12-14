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
        public ICollection<RelationshipTag> GetRelationshipTags()
        {
            SocialGameBLLDbContext db = new SocialGameBLLDbContext();
            ICollection<RelationTagEntity> RelationTagEntities = db.RelationTags.ToList();

            ICollection<RelationshipTag> RelationshipTags = ConvertRelationTagEntitiesToRelationshipTag(RelationTagEntities);
            return RelationshipTags;
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
    }
}