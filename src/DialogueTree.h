#pragma once
#include "DialogueNode.h"

/**
	Represents a set of dialogue texts and responses in the form of a
	directed graph. Responses to the text on one node may link to another
	node, which contains its own text and responses.
 */
class DialogueTree
{
public:
	// Constructors
	DialogueTree();
	~DialogueTree();

	// Accessors
	std::vector<DialogueNode*>& getDialogueNodes();
	DialogueNode* getFirstNode() const;
	DialogueNode* getDialogueNodeWithID(unsigned int) const;
	int getNumNodes() const;

	// Modifiers
	void addDialogueNode(unsigned int, std::string);
	void removeDialogueNode(unsigned int);
	void removeAllDialogueNodes();

private:
	// Private members
	std::vector<DialogueNode*> nodes;
}; //end class