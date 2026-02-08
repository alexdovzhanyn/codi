#include <iostream>
#include <cstdio>

class DiffGetter {
    public:

        std::string getDiff() {
            FILE* pipe = popen("git diff", "r");
            if (!pipe) return "";

            std::string output;
            char buffer[256];

            while(fgets(buffer, sizeof(buffer), pipe)) {
                output += buffer;
            }

            pclose(pipe);
            return output;
        }
};