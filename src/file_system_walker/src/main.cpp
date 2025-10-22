#include <chrono>
#include <iostream>
#include "rclcpp/rclcpp.hpp"
#include "file_system_messages/msg/scan_items.hpp"

using namespace std::chrono_literals;

class FileSystemWalker : public rclcpp::Node {
    public:
        FileSystemWalker() : Node("file_system_nodee")  {
            publisher_ = this->create_publisher<file_system_messages::msg::ScanItems>("FileSystemScanTopic", 1);
            timer_ = this->create_wall_timer(500ms, 
                [this]() {
                this->timerCallBack();
            });
        }
    private:
    void timerCallBack() {
        file_system_messages::msg::ScanItems msg;
        msg.files.push_back("file1");
        msg.files.push_back("file2");
        msg.folders.push_back("folder1");
        msg.folders.push_back("folder2");
        publisher_->publish(std::move(msg));
        std::cout<<"Send\n";
    }
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<file_system_messages::msg::ScanItems>::SharedPtr publisher_;


};

int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<FileSystemWalker>());
    rclcpp::shutdown();
    return 0;
}