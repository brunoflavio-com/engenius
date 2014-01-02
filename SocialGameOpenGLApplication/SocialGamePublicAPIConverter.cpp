#include "SocialGamePublicAPIConverter.h"


SocialGamePublicAPIConverter::SocialGamePublicAPIConverter()
{
}


SocialGamePublicAPIConverter::~SocialGamePublicAPIConverter()
{
}

User * SocialGamePublicAPIConverter::convertGraph(ns5__Graph * graph, string email){

	for (unsigned int i = 0; i < graph->RelationshipTags->RelationshipTag.size(); i++){
		ns5__RelationshipTag * ns5__relationshipTag = graph->RelationshipTags->RelationshipTag.at(i);
		RelationshipTag * relationshipTag = new RelationshipTag();
		relationshipTag->id = *ns5__relationshipTag->Id;
		relationshipTag->name = *ns5__relationshipTag->Name;
		relationShipTags.push_back(relationshipTag);
	}

	for (unsigned int i = 0; i < graph->HumourStatus->HumourStatus.size(); i++){
		ns5__HumourStatus * ns5__humourStatus = graph->HumourStatus->HumourStatus.at(i);
		HumorStatus * humorStatusTemp = new HumorStatus();
		humorStatusTemp->id = *ns5__humourStatus->Id;
		humorStatusTemp->name = *ns5__humourStatus->Name;
		humorStatus.push_back(humorStatusTemp);
	}

	for (unsigned int i = 0; i < graph->Interests->Interest.size(); i++){
		ns5__Interest * ns5__interest = graph->Interests->Interest.at(i);
		UserTag * userTag = new UserTag();
		userTag->id = *ns5__interest->Id;
		userTag->name = *ns5__interest->Name;
		userTags.push_back(userTag);
	}

	for (unsigned int i = 0; i < graph->Users->User.size(); i++){
		ns5__User * ns5__user = graph->Users->User.at(i);
		User * user = new User();
		
		user->email = *ns5__user->Email;

		if (ns5__user->Name != NULL){
			user->name = *ns5__user->Name;
		}
		if (ns5__user->Surname != NULL){
			user->surname = *ns5__user->Surname;
		}
		user->humor = getHumorStatus(*ns5__user->HumourStatusId);
		for (int i = 0; i < graph->Interests->Interest.size(); i++){
			UserTag * userTag = getUserTag(*graph->Interests->Interest.at(i)->Id);
			user->userTags.push_back(userTag);
		}
		
		users.push_back(user);
	}
	
	for (unsigned int i = 0; i < graph->Relationships->Relationship.size(); i++){
	ns5__Relationship * ns5__relationship	= graph->Relationships->Relationship.at(i);
	Relationship * relationship = new Relationship();
	User * userA = getUser(*ns5__relationship->UserAEmail);
	User * userB = getUser(*ns5__relationship->UserBEmail);
	RelationshipTag * relationshipTag = getRelationshipTag(*ns5__relationship->RelationshipTagId);
	relationship->user = userB;
	relationship->strength = *ns5__relationship->Strength;
	relationship->relationshipTag = relationshipTag;
	userA->relationships.push_back(relationship);
	}
		return getUser(email);

}

HumorStatus *  SocialGamePublicAPIConverter::getHumorStatus(int id){
	for (unsigned int i = 0; i < humorStatus.size(); i++){
		if (humorStatus.at(i)->id == id)
		{
			return humorStatus.at(i);
		}
	}
}

UserTag *  SocialGamePublicAPIConverter::getUserTag(int id){
	for (unsigned int i = 0; i < userTags.size(); i++){
		if (userTags.at(i)->id == id)
		{
			return userTags.at(i);
		}
	}
}

User *  SocialGamePublicAPIConverter::getUser(string email){
	for (unsigned int i = 0; i < users.size(); i++){
		
		 if (email.compare(users.at(i)->email) == 0)
		{
			return users.at(i);
		}
	}


}

RelationshipTag *  SocialGamePublicAPIConverter::getRelationshipTag(int id){
	for (unsigned int i = 0; i < relationShipTags.size(); i++){
		
		if (relationShipTags.at(i)->id == id)
		{
			return relationShipTags.at(i);
		}
	}
}