/*
https://leetcode.com/problems/design-most-recently-used-queue/
1756. Design Most Recently Used Queue
Medium

100

7

Add to List

Share
Design a queue-like data structure that moves the most recently used element to the end of the queue.

Implement the MRUQueue class:

MRUQueue(int n) constructs the MRUQueue with n elements: [1,2,3,...,n].
int fetch(int k) moves the kth element (1-indexed) to the end of the queue and returns it.
 

Example 1:

Input:
["MRUQueue", "fetch", "fetch", "fetch", "fetch"]
[[8], [3], [5], [2], [8]]
Output:
[null, 3, 6, 2, 2]

Explanation:
MRUQueue mRUQueue = new MRUQueue(8); // Initializes the queue to [1,2,3,4,5,6,7,8].
mRUQueue.fetch(3); // Moves the 3rd element (3) to the end of the queue to become [1,2,4,5,6,7,8,3] and returns it.
mRUQueue.fetch(5); // Moves the 5th element (6) to the end of the queue to become [1,2,4,5,7,8,3,6] and returns it.
mRUQueue.fetch(2); // Moves the 2nd element (2) to the end of the queue to become [1,4,5,7,8,3,6,2] and returns it.
mRUQueue.fetch(8); // The 8th element (2) is already at the end of the queue so just return it.
 

Constraints:

1 <= n <= 2000
1 <= k <= n
At most 2000 calls will be made to fetch.
 

Follow up: Finding an O(n) algorithm per fetch is a bit easy. Can you find an algorithm with a better complexity for each fetch call?
*/

// Time:  ctor:  O(n + m), m is the max number of calls
// Space: fetch: O(log(n + m))

class MRUQueue
{
public:
    MRUQueue(int n)
        : bit_{n}, curr_{n}
    {
        for (int i = 0; i < n; ++i)
        {
            lookup_[i] = i + 1;
        }
    }

    int fetch(int k)
    {
        int pos = bit_.binary_lift(k);
        int val = lookup_[pos];
        lookup_.erase(pos);
        bit_.add(pos, -1);
        bit_.add(curr_, 1);
        lookup_[curr_++] = val;
        return val;
    }

private:
    class BIT
    {
    public:
        static const int MAX_CALLS = 2000;

        BIT(int n) : bit_(n + MAX_CALLS + 1)
        { // 0-indexed
            for (int i = 1; i < size(bit_); ++i)
            {
                bit_[i] = ((i - 1 < n) ? 1 : 0) + bit_[i - 1];
            }
            for (int i = size(bit_) - 1; i >= 1; --i)
            {
                int last_i = i - lower_bit(i);
                bit_[i] -= bit_[last_i];
            }
        }

        void add(int i, int val)
        {
            ++i;
            for (; i < size(bit_); i += lower_bit(i))
            {
                bit_[i] += val;
            }
        }

        int query(int i) const
        {
            ++i;
            int total = 0;
            for (; i > 0; i -= lower_bit(i))
            {
                total += bit_[i];
            }
            return total;
        }

        int binary_lift(int k) const
        {
            int total = 0;
            int pos = 0;
            for (int i = floor_log2_x(size(bit_) - 1); i >= 0; --i)
            {
                if (pos + (1 << i) < size(bit_) && !(total + bit_[pos + (1 << i)] >= k))
                {
                    total += bit_[pos + (1 << i)];
                    pos += (1 << i);
                }
            }
            return (pos + 1) - 1;
        }

    private:
        int lower_bit(int i) const
        {
            return i & -i;
        }

        int floor_log2_x(int x) const
        {
            return 8 * sizeof(int) - __builtin_clz(x) - 1;
        };

        vector<int> bit_;
    };

    BIT bit_;
    unordered_map<int, int> lookup_;
    int curr_;
};

// Time:  ctor:  O(n)
// Space: fetch: O(sqrt(n))
// sqrt decomposition solution
class MRUQueue2
{
public:
    MRUQueue2(int n)
        : buckets_(ceil(sqrt(n)))
    {
        for (int i = 0; i < n; ++i)
        {
            buckets_[i / size(buckets_)].emplace_back(i + 1);
        }
    }

    int fetch(int k)
    {
        --k;
        int left = k / size(buckets_);
        int idx = k % size(buckets_);
        auto cit = cbegin(buckets_[left]);
        advance(cit, idx);
        int val = *cit;
        buckets_[left].erase(cit);
        buckets_.back().emplace_back(val);
        for (int i = size(buckets_) - 2; i >= left; --i)
        {
            int x = buckets_[i + 1].front();
            buckets_[i + 1].pop_front();
            buckets_[i].emplace_back(x);
        }
        return val;
    }

private:
    vector<list<int> > buckets_;
};