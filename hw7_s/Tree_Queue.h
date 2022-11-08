typedef TreeNode* dElement;

typedef struct tQueueNode {
	dElement data;
	struct tQueueNode *next;
} QueueNode;

typedef struct {
	int count;	// # of elements
	QueueNode *front, *rear;	// front and rear
} Queue;

Queue* CreateQueue()
// size is not used
{
	Queue *pNewQueue = (Queue*)malloc(sizeof(Queue));	
	if(pNewQueue == NULL)
		return NULL;

	pNewQueue->count = 0;
	pNewQueue->front = pNewQueue->rear = NULL;

	return pNewQueue;
}

void Enqueue(Queue *pQueue, dElement item)
{
	QueueNode *pNewNode = (QueueNode*) malloc(sizeof(QueueNode));
	if(pNewNode == NULL)
		return;
	pNewNode->data = item;
	pNewNode->next = NULL;

	if(pQueue->count <= 0){
		pQueue->front = pQueue->rear = pNewNode;
	} else {
		pQueue->rear->next = pNewNode;
		pQueue->rear = pNewNode;	
	}

	pQueue->count++;	
}

bool IsEmptyQueue(Queue *pQueue)
{
  if(pQueue->count <= 0)
		return true;		// queue empty
  else
    return false;
}

dElement Front(Queue *pQueue)
{ 
	if(IsEmptyQueue(pQueue))
		return 0;		// queue empty

	return pQueue->front->data;
}

dElement Dequeue(Queue *pQueue)
{
	QueueNode *pFront = NULL;
	dElement item = NULL;
  
	if(IsEmptyQueue(pQueue))
		return 0;		// queue empty
  
	pFront = pQueue->front;
	item = pFront->data;
  
	if(pQueue->count == 1){
		pQueue->front = pQueue->rear = NULL;
	} else {
		pQueue->front = pFront->next;
	}

	free(pFront);
	pQueue->count--;

	return item;
}

void DestroyQueue(Queue *pQueue)
{
	QueueNode *pCur = NULL, *pNext = NULL;

	for(pCur = pQueue->front; pCur != NULL; pCur = pNext){
		pNext = pCur->next;
		free(pCur);
	}

	pQueue->count = 0;
	pQueue->front = pQueue->rear = NULL;

	free(pQueue);
}