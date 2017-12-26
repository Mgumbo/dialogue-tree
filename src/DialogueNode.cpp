#include "DialogueNode.h"

/**
	Standard constructor that initializes private members.

	@param nodeID  The unique ID for this node.
	@param text  The text that will be assigned to this node.
 */
DialogueNode::DialogueNode(unsigned int nodeID, std::string text) : id(nodeID), nodeText(text) { }

/**
	Destructor, called when the object instance is destroyed.
 */
DialogueNode::~DialogueNode()
{
	this->removeAllDialogueOptions();
} //end destructor

/**
	Returns the ID of this node.

	@return An unsigned int containing the ID of this node.
 */
unsigned int DialogueNode::getID() const
{
	return this->id;
} //end getID

/**
	Returns the text assigned to this node.

	@return A string containing the text assigned to this node.
 */
std::string DialogueNode::getText() const
{
	return this->nodeText;
} //end getText

/**
	Returns a reference this node's vector of DialogueOption pointers.

	@return A vector of DialogueOption pointers.
 */
std::vector<DialogueNode::DialogueOption*>& DialogueNode::getOptions()
{
	return this->options;
} //end getOptions

/**
	Returns the number of DialogueOptions contained in this node.

	@return An int representing the number of DialogueOptions in this node.
 */
int DialogueNode::getNumOptions() const
{
	return this->options.size();
} //end getNumOptions

/**
	Creates and appends a new DialogueOption to the node.

	@param optText  The text assigned to the DialogueOption.
	@param nextNode  The DialogueNode that the new DialogueOption is attached to.
	@param optionVal  A value associated with the DialogueOption. This parameter can be omitted and will default to 0.
 */
void DialogueNode::addDialogueOption(const std::string optText, DialogueNode* nextNode, const int optionVal)
{
	DialogueOption* newOpt = new DialogueOption(optText, nextNode, optionVal);
	this->options.push_back(newOpt);
} //end addDialogueOption

/**
	Removes and frees the memory allocated to a DialogueOption at a specified index.

	@param index  The index of the DialogueOption to be removed.
 */
void DialogueNode::removeDialogueOption(const int index)
{
	DialogueOption* tmp = this->options.at(index);
	this->options.erase(this->options.begin() + index);
	delete tmp;
} //end removeDialogueOption

/**
	Removes and frees the memory allocated to a DialogueOption with specific text.

	@param optText  The text to search for.
 */
void DialogueNode::removeDialogueOption(std::string optText)
{
	for (auto it = this->options.begin(); it != this->options.end(); ++it)
	{
		if ((*it)->optionText.compare(optText) == 0) //if the texts match
		{
			DialogueOption* tmp = *it;
			this->options.erase(it);
			delete tmp;
			break;
		} //end if
	} //end for
} //end removeDialogueOption

/**
	Removes and frees the memory allocated to each DialogueOption in the node.
 */
void DialogueNode::removeAllDialogueOptions()
{
	while (this->options.size() > 0)
		this->removeDialogueOption(0);
} //end removeAllDialogueOptions