namespace Threading {
    void RunAsync(std::function<void()> callback){
        {
            std::thread T(callback);
            T.detach();
        }
    }

    void Delay(int ms){
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
    }
}