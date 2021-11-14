/*
https://leetcode.com/problems/design-front-middle-back-queue/
1670. Design Front Middle Back Queue
Medium

336

64

Add to List

Share
Design a queue that supports push and pop operations in the front, middle, and back.

Implement the FrontMiddleBack class:

FrontMiddleBack() Initializes the queue.
void pushFront(int val) Adds val to the front of the queue.
void pushMiddle(int val) Adds val to the middle of the queue.
void pushBack(int val) Adds val to the back of the queue.
int popFront() Removes the front element of the queue and returns it. If the queue is empty, return -1.
int popMiddle() Removes the middle element of the queue and returns it. If the queue is empty, return -1.
int popBack() Removes the back element of the queue and returns it. If the queue is empty, return -1.
Notice that when there are two middle position choices, the operation is performed on the frontmost middle position choice. For example:

Pushing 6 into the middle of [1, 2, 3, 4, 5] results in [1, 2, 6, 3, 4, 5].
Popping the middle from [1, 2, 3, 4, 5, 6] returns 3 and results in [1, 2, 4, 5, 6].
 

Example 1:

Input:
["FrontMiddleBackQueue", "pushFront", "pushBack", "pushMiddle", "pushMiddle", "popFront", "popMiddle", "popMiddle", "popBack", "popFront"]
[[], [1], [2], [3], [4], [], [], [], [], []]
Output:
[null, null, null, null, null, 1, 3, 4, 2, -1]

Explanation:
FrontMiddleBackQueue q = new FrontMiddleBackQueue();
q.pushFront(1);   // [1]
q.pushBack(2);    // [1, 2]
q.pushMiddle(3);  // [1, 3, 2]
q.pushMiddle(4);  // [1, 4, 3, 2]
q.popFront();     // return 1 -> [4, 3, 2]
q.popMiddle();    // return 3 -> [4, 2]
q.popMiddle();    // return 4 -> [2]
q.popBack();      // return 2 -> []
q.popFront();     // return -1 -> [] (The queue is empty)
 

Constraints:

1 <= val <= 109
At most 1000 calls will be made to pushFront, pushMiddle, pushBack, popFront, popMiddle, and popBack.
*/

// Time:  O(1)
// Space: O(n)

class FrontMiddleBackQueue
{
public:
    FrontMiddleBackQueue()
    {
    }

    void pushFront(int val)
    {
        left_.emplace_front(val);
        balance();
    }

    void pushMiddle(int val)
    {
        if (size(left_) > size(right_))
        {
            right_.emplace_front(left_.back());
            left_.pop_back();
        }
        left_.emplace_back(val);
    }

    void pushBack(int val)
    {
        right_.emplace_back(val);
        balance();
    }

    int popFront()
    {
        int result = -1;
        if (!empty(left_))
        {
            result = left_.front();
            left_.pop_front();
        }
        balance();
        return result;
    }

    int popMiddle()
    {
        int result = -1;
        if (!empty(left_))
        {
            result = left_.back();
            left_.pop_back();
        }
        balance();
        return result;
    }

    int popBack()
    {
        int result = -1;
        if (!empty(right_))
        {
            result = right_.back();
            right_.pop_back();
        }
        else if (!empty(left_))
        {
            result = left_.back();
            left_.pop_back();
        }
        balance();
        return result;
    }

private:
    void balance()
    {
        if (size(left_) > size(right_) + 1)
        {
            right_.emplace_front(left_.back());
            left_.pop_back();
        }
        else if (size(left_) < size(right_))
        {
            left_.emplace_back(right_.front());
            right_.pop_front();
        }
    }

    // using list<int> is also fine but slower
    deque<int> left_;
    deque<int> right_;
};