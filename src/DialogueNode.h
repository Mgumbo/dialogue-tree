#pragma once
#include <string>
#include <vector>

/**
	Represents an individual node of a DialogueTree. Each node contains text
	and a set of options that serve as responses to the node's text.
 */
class DialogueNode
{
	// Forward declare struct, private access by default
	struct DialogueOption;

public:
	// Constructors
	DialogueNode(unsigned int, std::string);
	~DialogueNode();
	
	// Accessors
	unsigned int getID() const;
	std::string getText() const;
	std::vector<DialogueOption*>& getOptions();
	int getNumOptions() const;

	// Modifiers
	void addDialogueOption(std::string, DialogueNode*, const int = 0);
	void removeDialogueOption(std::string);
	void removeDialogueOption(int);
	void removeAllDialogueOptions();

private:
	// Private members
	unsigned int id;
	const std::string nodeText;
	std::vector<DialogueOption*> options;

	/**
		Represents a response to the DialogueNode's text. Each option has its own text,
		a pointer to another DialogueNode, and a value associated with the option.
	 */
	struct DialogueOption
	{
		/**
			Standard constructor for a DialogueOption.

			@param text  The text associated with this DialogueOption.
			@param next  A DialogueNode that would be displayed following this DialogueOption being selected.
			@param val  A specific, but not necessarily unique, value associated with this DialogueOption.
		 */
		DialogueOption(std::string text, DialogueNode* next, const int val = 0) : optionText(text), nextNode(next), optionVal(val) { };

		// Struct members
		std::string optionText;
		DialogueNode* nextNode;
		const int optionVal; //this might be used as a trigger based on the value
	}; //end struct
}; //end class