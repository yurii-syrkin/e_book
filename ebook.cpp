#include <algorithm>
#include <array>
#include <iomanip>
#include <iostream> 
#include <vector>
#include <numeric>

const size_t MAX_USERS_QUANTITY = 100001;
const size_t MAX_PAGE_NUMBER = 1001;

class Ebook{
    public:
        Ebook(int number_of_requests)
            : number_of_requests_(number_of_requests){
                pages_ = {};
                charts_ = {};
            }

        void ProcessRequests(){
            for (int i = 0; i < number_of_requests_; ++i){
                std::string command;
                int user_id;
                int page;
                std::cin >> command;
                std::cin >> user_id;
                if (command == "READ") {
                    std::cin >> page;
                    ProcessRequest(command, user_id, page);
                }else if (command == "CHEER") {
                    ProcessRequest(command, user_id);
                }
            }
        }

        void ProcessRequest(std::string& command, int user_id, int page = -1){
            if (command == "READ") {                
                CommandREAD(user_id, page);
            }else if (command == "CHEER") {
                CommandCHEER(user_id);
            }
        }

    private:
        int number_of_requests_;
        double users_all_ = 0;
        std::array<int, MAX_USERS_QUANTITY> pages_;
        std::array<int, MAX_PAGE_NUMBER> charts_;        
        void CommandREAD(int user_id, int page){
            if (pages_[user_id] == 0){
                ++users_all_;
            }
            int page_quantity_of_current_user = pages_[user_id];
            if (charts_[page_quantity_of_current_user] > 0 ){
                --charts_[page_quantity_of_current_user];
            }
            ++charts_[page];
            pages_[user_id] = page;
            charts_[0] = 0;
        }
        void CommandCHEER(int user_id){            
            if (pages_.size() == 0) {
                std::cout << 0 << std::endl;
            } else if (pages_[user_id] == 0) {
                std::cout << 0 << std::endl;
            } else {
                if (users_all_ == 1) {
                    std::cout << 1 << std::endl;
                } else {
                    std::vector<int> test{charts_.begin(), charts_.begin() + pages_[user_id]};
                    double users_with_min_result = std::accumulate(charts_.begin(), charts_.begin() + pages_[user_id], 0);
                    
                    double result = users_with_min_result/(users_all_ - 1);
                    std::cout << std::setprecision(6);
                    std::cout << result << std::endl;
                }
            }
        }
};

int main(){
    int number_of_reauests;
    std::cin >> number_of_reauests;

    Ebook ebook(number_of_reauests);
    ebook.ProcessRequests();    
}