json(
  [	
    Relationships=
      [	
	json(
	  [
	    RelationshipTagId=1,
	    Strength=2,
	    UserAEmail=test@test.com,
	    UserBEmail=test3@test.com
	  ]
	),
	json(
	  [
	    RelationshipTagId=2,
	    Strength=5,
	    UserAEmail=test2@test.com,
	    UserBEmail=test3@test.com
	  ]
	),
	json(
	  [
	    RelationshipTagId=1,
	    Strength=5,
	    UserAEmail=test@test.com,
	    UserBEmail=test2@test.com
	  ]
	)
      ],
    Users=
      [
	json(
	  [
	    Birthdate=0001-01-01T00:00:00,
	    Email=test3@test.com,
	    FacebookProfile= @null,
	    HumourStatusId=1,
	    InterestsIDs=[1,2,3,4],
	    LinkedInProfile= @null,
	    Name= @null,
	    PhoneNumber= @null,
	    Surname= @null
	  ]
	),
	json(
	  [
	    Birthdate=0001-01-01T00:00:00,
	    Email=test@test.com,
	    FacebookProfile= @null,
	    HumourStatusId=1,
	    InterestsIDs=[1],
	    LinkedInProfile= @null,
	    Name= @null,
	    PhoneNumber= @null,
	    Surname= @null
	  ]
	),
	json(
	  [
	    Birthdate=0001-01-01T00:00:00,
	    Email=test2@test.com,
	    FacebookProfile= @null,
	    HumourStatusId=1,
	    InterestsIDs=[],
	    LinkedInProfile= @null,
	    Name= @null,
	    PhoneNumber= @null,
	    Surname= @null
	  ]
	)
      ]
  ]
)