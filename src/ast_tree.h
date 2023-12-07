enum OP
{
	AND = '&',
	OR = '|',
};

typedef struct
{
	int idx;
	bool isLeaf;
} AstBaseNode;

typedef struct AstInnerNode
{
	int idx;
	bool isLeaf;
	int val;
	OP operatorr;
	AstBaseNode *left;
	AstBaseNode *right;

	AstInnerNode(OP op)
	{
		idx = -1;
		isLeaf = false;
		val = -2;
		operatorr = op;
		left = nullptr;
		right = nullptr;
	}
} AstInnerNode;

typedef struct AstLeafNode
{
	int idx;
	bool isLeaf;
	unsigned int wordId;

	AstLeafNode(int wordIdd)
	{
		idx = -1;
		isLeaf = true;
		wordId = wordIdd;
	}

} AstLeafNode;
