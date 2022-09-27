#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>



namespace part2 {
    template <typename T, typename F>
    void iter(T* p_array, size_t array_size, F callback) {
        for (size_t i = 0; i < array_size; i++) {
            (void)callback(p_array[i]);
        }
    }

    class RadixSort
    {
    public:
        RadixSort(){};
        virtual ~RadixSort(){};

        void sort(std::vector<int> &nums);

    private:
        int maxNum, div;
        std::vector<std::vector<int>> buckets;

    };

    void RadixSort::sort(std::vector<int> &nums)
    {
        if(nums.empty())
            return;

        buckets.resize(10);
        maxNum = *(std::max_element(nums.begin(),nums.end()));

        int i=1;
        while(maxNum != 0)
        {
        // Move numbers into appropriate buckets
        for(auto num : nums)
        {
            if(num<0)
                throw std::domain_error("For radix sort , array cannot contain negative value. ");

            int remainder = (num/i)%10;
            buckets[remainder].push_back(num);
        }

        // Now, move numbers from bucket to original array
        nums.clear();
        for(auto bucket1:buckets)
        {
            for(auto bucket2: bucket1)
            {
                nums.push_back(bucket2);
            }

        }
        for(int j=0; j<10; j++)
        {
            buckets[j].clear();
        }

        maxNum/=10;
        i *= 10;
        }
    }

    void custom_sort(std::vector<int> &nums) {
        RadixSort rs;
        rs.sort(nums);
        return;
    }

    void custom_sort(std::vector<double> &nums) {
        std::sort(std::begin(nums), std::end(nums));
        return;
    }

    void custom_sort(std::vector<float> &nums) {
        std::sort(std::begin(nums), std::end(nums));
        return;
    }

    //template of factorial
    template<int64_t n>
    class Factorial {
    public:
        static constexpr int64_t value = Factorial<n - 1>::value * n;
    };

    template<>
    class Factorial<0> {
    public:        
        static constexpr int64_t value = 1;
    };

}
