using System;
using System.Collections.Generic;
using System.Data.Entity;
using System.Linq;
using System.Web;

namespace SocialGameBLL.Entities
{
    public class SocialGameBLLDbContext : DbContext
    {
        DbSet<UserEntity> Users { get; set; }
        DbSet<UserSecurity> Passwords { get; set; }
        DbSet<RelationshipEntity> Relationships { get; set; }
        DbSet<RelationshipRequestEntity> RelationshipsRequests { get; set; }
        DbSet<InterestEntity> Interests { get; set; }
        DbSet<HumourStatusEntity> HumourStatus { get; set; }
        DbSet<RelationTagEntity> RelationTags {get; set;}

        protected override void OnModelCreating(DbModelBuilder modelBuilder)
        {
            base.OnModelCreating(modelBuilder);

            modelBuilder.Entity<RelationshipEntity>()
                .HasRequired<UserEntity>(r => r.User)
                .WithMany(u => u.UserRelationships)
                .HasForeignKey(r2 => r2.UserEmail)
                .WillCascadeOnDelete(false);

            modelBuilder.Entity<RelationshipEntity>()
                .HasRequired<UserEntity>(r => r.Friend)
                .WithMany(u => u.RelationshipsWithUser)
                .HasForeignKey(r2 => r2.FriendEmail)
                .WillCascadeOnDelete(false);

            modelBuilder.Entity<RelationshipRequestEntity>()
                .HasRequired<UserEntity>(r => r.User)
                .WithMany(u => u.RequestsSent)
                .HasForeignKey(r2 => r2.UserEmail)
                .WillCascadeOnDelete(false);

            modelBuilder.Entity<RelationshipRequestEntity>()
                .HasRequired<UserEntity>(r => r.User)
                .WithMany(u => u.RequestsReceived)
                .HasForeignKey(r2 => r2.UserEmail)
                .WillCascadeOnDelete(false);
        }
    }
}