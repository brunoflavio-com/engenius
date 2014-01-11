using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace SocialGameBLL.Entities
{
    public class InterestEntity
    {
        public int ID { get; set; }

        public string FreebaseId { get; set; }

        public string Name { get; set; }

        public virtual ICollection<UserEntity> Users { get; set; }
    }
}