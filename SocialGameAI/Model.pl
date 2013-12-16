%
% FILE: Model.pl
%

%
% Social Game AI Model:
%

%%
% User:
% Json definition:
%    {
%      "Birthdate": "0001-01-01T00:00:00",
%      "Email": "test@test.com",
%      "FacebookProfile": null,
%      "HumourStatusId": 1,
%      "InterestsIDs": [
%        1
%      ],
%      "LinkedInProfile": null,
%      "Name": null,
%      "PhoneNumber": null,
%      "Surname": null
%    }
%
% Prolog fact:
% user(Email, Name, Surname, Birthdate, PhoneNumber, HumourStatusID, FacebookProfile, LinkedInProfile)
:-dynamic(user/8).

%%
% User Interests:
%
% interest(Email, InterestID).
:-dynamic(interest/2).

%%
% Relationship:
% Json definition:
%  {
%      "RelationshipTagId": 1,
%      "Strength": 2,
%      "UserAEmail": "test@test.com",
%      "UserBEmail": "test3@test.com"
%   }
%
% Prolog fact:
% relationship(EmailA, EmailB, TagID, Strength).
:-dynamic(relationship/4).
 
  

