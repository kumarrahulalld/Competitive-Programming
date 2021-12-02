//Priority queue
//Runtime: 84 ms, faster than 14.51% of C++ online submissions for Kth Smallest Element in a Sorted Matrix.
//Memory Usage: 12.4 MB, less than 59.09% of C++ online submissions for Kth Smallest Element in a Sorted Matrix.
class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        priority_queue<int, vector<int>, less<int>> pq;
        
        for(int i = 0; i < matrix.size(); i++){
            for(int j = 0; j < matrix[0].size(); j++){
                pq.push(matrix[i][j]);
                if(pq.size() > k){
                    cout << "pop: " << pq.top() << endl;
                    pq.pop();
                }
            }
        }
        
        //the answer is the k-th smallest element,
        //which is the smallest element in the heap of size k
        return pq.top();
    }
};

//Priority queue(optimized)
//https://leetcode.com/problems/kth-smallest-element-in-a-sorted-matrix/discuss/85173/Share-my-thoughts-and-Clean-Java-Code
//Runtime: 68 ms, faster than 27.19% of C++ online submissions for Kth Smallest Element in a Sorted Matrix.
//Memory Usage: 14.2 MB, less than 9.09% of C++ online submissions for Kth Smallest Element in a Sorted Matrix.
class Tuple{
public:
    int x;
    int y;
    int val;
    Tuple(int x, int y, int val) : x(x), y(y), val(val) {};
};

class TupleGreater{
public:
    TupleGreater(){}
    bool operator() (const Tuple* lhs, const Tuple* rhs) const{
        return lhs->val > rhs->val;
    }
};

class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        priority_queue<Tuple*, vector<Tuple*>, TupleGreater> pq;
        //push first row into pq
        for(int y = 0; y < matrix[0].size(); y++){
            pq.push(new Tuple(0, y, matrix[0][y]));
        }
        
        k--;
        //do k-1 times, a.k.a, pop the smaller k-1 elements
        while(k-- > 0){
            Tuple* t = pq.top(); pq.pop();
            // cout << "pop: " << t->val << endl;
            if(t->x+1 == matrix.size()) continue;
            pq.push(new Tuple(t->x+1, t->y, matrix[t->x+1][t->y]));
        }
        
        //now the top of pq is k th smallest element
        return pq.top()->val;
    }
};

//Solution 2 : Binary Search in range
//https://leetcode.com/problems/kth-smallest-element-in-a-sorted-matrix/discuss/85173/Share-my-thoughts-and-Clean-Java-Code
//Runtime: 36 ms, faster than 94.39% of C++ online submissions for Kth Smallest Element in a Sorted Matrix.
//Memory Usage: 11.1 MB, less than 100.00% of C++ online submissions for Kth Smallest Element in a Sorted Matrix.
class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int m = matrix.size(), n = matrix[0].size();
        int lo = matrix[0][0], hi = matrix[m - 1][n - 1] + 1;//[lo, hi)
        //hi is exclusive, so not "lo <= hi"!!
        while(lo < hi) {
            /*
            lo: -5, hi: -4
            we want mid to be -5(hi is exclusive)
            using  mid = (hi + lo) / 2", we get -4
            using "mid = lo + (hi - lo) / 2", we get -5
            */
            // int mid = (hi + lo) / 2; //should not use this!!!
            //this makes mid closer to lo
            int mid = lo + (hi - lo) / 2; //should use this!!!
            // cout << "range: " << lo << " " << mid << " " << hi << endl;
            //get the number of elements <= mid
            int count = 0;
            for(int i = 0; i < m; i++) {
                int j = n - 1;
                while(j >= 0 && matrix[i][j] > mid) j--;
                //for current row, matrix[i][0] ~ matrix[i][j] <= mid
                count += (j + 1);
                // cout << i << " " << j << " " << count << endl;
            }
            //mid is count-th smallest number
            //if count < k, we need to increase the lower bound of search range
            //if count >= k, we set hi = mid to find smallest possible value
            if(count < k) lo = mid + 1;
            else hi = mid; //hi is exclusive, so not "hi = mid-1;"!!
            // cout << "====================" << endl;
        }
        return lo;
    }
};

//findNSum, recursive, optimized
//https://leetcode.com/problems/4sum/discuss/8545/Python-140ms-beats-100-and-works-for-N-sum-(Ngreater2)
//Runtime: 8 ms, faster than 98.35% of C++ online submissions for 4Sum.
//Memory Usage: 8.5 MB, less than 100.00% of C++ online submissions for 4Sum.
class Solution {
public:
    void findNSum(int l, int r, int target, int N, vector<int>& nums, vector<int>& result, vector<vector<int>>& results){
        if(r-l+1 < N || N < 2 || target < nums[l]*N || target > nums[r]*N){
            //r-l+1 < N: range's width should >= N
            return;
        }
        if(N == 2){
            while(l < r){
                if(nums[l] + nums[r] == target){
                    result.push_back(nums[l]);
                    result.push_back(nums[r]);
                    // cout << "result: " << endl;
                    // for(int i = 0; i < result.size(); i++){
                    //     cout << result[i] << " ";
                    // }
                    // cout << endl;
                    results.push_back(result);
                    //need to revert the push_back above for later use!
                    result.pop_back();
                    result.pop_back();
                    while(l < r && nums[l] == nums[l+1]){
                        l++;
                    }
                    l++;
                    while(l < r && nums[r] == nums[r-1]){
                        r--;
                    }
                    r--;
                }else if(nums[l] + nums[r] < target){
                    l++;
                }else{
                    r--;
                }
            }
        }else{
            //recursively reduce N
            //i <= r+1-N: because r-i+1 should >= N
            for(int i = l; i <= r+1-N; i++){
                //skip duplicate nums[i]
                if(i == l || (i > l && nums[i] != nums[i-1])){
                    result.push_back(nums[i]);
                    // cout << "i: " << i << ", nums[i]: " << nums[i] << ", [" << i+1 << ",  " << r  << "], target: " << target-nums[i] << " , N: " << N-1 << endl;
                    findNSum(i+1, r, target-nums[i], N-1, nums, result, results);
                    //need to revert the push_back above for later use!
                    result.pop_back();
                }
            }
        }
    };
    
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        // for(int i = 0; i < nums.size(); i++){
        //     cout << nums[i] << " ";
        // }
        // cout << endl;
        vector<int> result;
        vector<vector<int>> results;
        findNSum(0, nums.size()-1, target, 4, nums, result, results);
        return results;
    }
};
