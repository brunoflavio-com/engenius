namespace SocialGameBLL.Migrations
{
    using SocialGameBLL.Entities;
    using SocialGameBLL.Security;
    using System;
    using System.Collections.Generic;
    using System.Data.Entity;
    using System.Data.Entity.Migrations;
    using System.Linq;

    internal sealed class Configuration : DbMigrationsConfiguration<SocialGameBLL.Entities.SocialGameBLLDbContext>
    {
        public Configuration()
        {
            AutomaticMigrationsEnabled = false;
        }

        protected override void Seed(SocialGameBLL.Entities.SocialGameBLLDbContext context)
        {
            var interests = new List<InterestEntity>
            {
                new InterestEntity{
                    Name = "Sport"
                },
                new InterestEntity{
                    Name = "Technology"
                }
            };
            interests.ForEach(i => context.Interests.AddOrUpdate(p => p.Name, i));
            context.SaveChanges();

            var humourstatus = new List<HumourStatusEntity>
            {
                new HumourStatusEntity{
                    Name = "Normal"
                },
                new HumourStatusEntity{
                    Name = "Happy"
                }
            };
            humourstatus.ForEach(h => context.HumourStatus.AddOrUpdate(p => p.Name, h));

            var relationstag = new List<RelationTagEntity>
            {
                new RelationTagEntity{
                    Name = "Family"
                },
                new RelationTagEntity{
                    Name = "Friend"
                }
            };
            relationstag.ForEach(r => context.RelationTags.AddOrUpdate(p => p.Name, r));
            context.SaveChanges();

            var emails = new List<string>
            {
                "test@test.com","test2@test.com","test3@test.com","test4@test.com","test5@test.com","test6@test.com","test7@test.com","test8@test.com","test9@test.com"
            };

            var users = new List<UserEntity>(emails.Count);

            for(int i = 0; i < emails.Count; i++)
            {
                try
                {
                    users.Add(SecurityService.RegisterUser(emails[i], "123456"));
                }
                catch (Exception e)
                {
                    users.Add(context.Users.Find(emails[i]));
                }
            }

            var relationships = new List<RelationshipEntity>
            {
                new RelationshipEntity{
                    UserEmail = users[0].Email,
                    FriendEmail = users[1].Email,
                    RelationTagID = 1,
                    Strength = 4
                },
                new RelationshipEntity{
                    UserEmail = users[0].Email,
                    FriendEmail = users[2].Email,
                    RelationTagID = 2,
                    Strength = 3
                },
                new RelationshipEntity{
                    UserEmail = users[2].Email,
                    FriendEmail = users[1].Email,
                    RelationTagID = 2,
                    Strength = 4
                },
                new RelationshipEntity{
                    UserEmail = users[2].Email,
                    FriendEmail = users[3].Email,
                    RelationTagID = 1,
                    Strength = 4
                },
                new RelationshipEntity{
                    UserEmail = users[3].Email,
                    FriendEmail = users[1].Email,
                    RelationTagID = 2,
                    Strength = 6
                },
                new RelationshipEntity{
                    UserEmail = users[3].Email,
                    FriendEmail = users[4].Email,
                    RelationTagID = 2,
                    Strength = 3
                },
                new RelationshipEntity{
                    UserEmail = users[1].Email,
                    FriendEmail = users[5].Email,
                    RelationTagID = 1,
                    Strength = 1
                },
                new RelationshipEntity{
                    UserEmail = users[2].Email,
                    FriendEmail = users[6].Email,
                    RelationTagID = 2,
                    Strength = 3
                },
                new RelationshipEntity{
                    UserEmail = users[2].Email,
                    FriendEmail = users[8].Email,
                    RelationTagID = 1,
                    Strength = 4
                },
                new RelationshipEntity{
                    UserEmail = users[0].Email,
                    FriendEmail = users[7].Email,
                    RelationTagID = 2,
                    Strength = 8
                },
                new RelationshipEntity{
                    UserEmail = users[0].Email,
                    FriendEmail = users[6].Email,
                    RelationTagID = 2,
                    Strength = 4
                },
            };
            relationships.ForEach(r => context.Relationships.AddOrUpdate(p => new { p.UserEmail, p.FriendEmail }, r));
            context.SaveChanges();
        }
    }
}
