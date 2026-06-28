#include <iostream>
#include <stdio.h>
#include <unistd.h>
//#include <sys/inotify.h>
using namespace std;

string DetectOS() {
#if defined(_WIN64) || defined(_WIN32)
    return "windows";

# elif  defined(__linux__)
    return "linux";

#endif
}

void LinuxFIM(string file) {/*
#define BUF_LEN (1024 * (sizeof(struct inotify_event) + 16))
    int fd = inotify_init();
    if (fd < 0) { perror("inotify_init"); exit(1); }

    int wd = inotify_add_watch(fd, file.c_str(), IN_MODIFY | IN_DELETE);
    if (wd < 0) { perror("inotify_add_watch"); exit(1); }

    char buffer[BUF_LEN];

    while (1) {
        int length = read(fd, buffer, BUF_LEN);

        if (length < 0) {
            perror("read");
            exit(1);
        }

        int i = 0;
        string action;
        while (i < length) {
            struct inotify_event *event =
                (struct inotify_event *) &buffer[i];
            if      (event->mask & IN_MODIFY) action = "modified";
            else if (event->mask & IN_DELETE) action = "deleted";
            else                              action = "other";

            if (event->len)
                printf("Event received: [%s] %s\n", action.c_str(), event->name);
            else
                printf("Event received: [%s]\n", action.c_str());

            i += sizeof(struct inotify_event) + event->len;
            cout << "i=" << i << endl;
        }
    }
*/
    cout << "Filename::::"<< file << endl;
}




