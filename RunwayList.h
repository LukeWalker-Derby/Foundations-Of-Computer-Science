//Struct of Runways
struct outerNode
{
	int value;
	int numChildren;
	struct outerNode* next;
	struct innerNode* child;
};

//Taking Off Aircraft
struct innerNode
{
	int value;
	int flightNo;
	struct innerNode* next;
};

//Incomming Aircraft
struct incomingNode
{
	int	fuel;
	int	time;
	int wait;
	int flightNo;
	int runway;
	int passengerNo;
	struct incomingNode* next;
};

struct outerNode* createOuterList();
struct outerNode* createOuterNode(int value, struct innerNode* child);
struct innerNode* createInnerList(struct outerNode** list);
struct innerNode* createInnerNode(int value, int flightNo);
void addOuterNode(struct outerNode** list, int value, struct innerNode* child);
void printOuterList(struct outerNode* list);
void increment(struct outerNode* l);
void addToNthList(struct outerNode* list, int n, int value, int flightNo);
void addInnerNode(struct outerNode* list, int value, int flightNo);
void printInnerList(struct innerNode* list);
void incrementTime(struct innerNode* l);
int lowestOccupiedRunway(struct outerNode* list, int index);
void removeFromRunway(struct outerNode* oList);
int getNumChildren(struct outerNode* list, int index);