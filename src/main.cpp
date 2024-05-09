#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>
#include <mpg123.h>
#undef main

int main(int argc, char *argv[]) {
    // Khởi tạo libmpg123
    if (mpg123_init() != MPG123_OK) {
        std::cerr << "mpg123_init failed" << std::endl;
        return 1;
    }

    // Mở tệp .mp3
    mpg123_handle* mh = mpg123_new(NULL, NULL);
    mpg123_id3v1 *id3v1;
    mpg123_id3v2 *id3v2;
    char *icy_meta;
    if (!mh) {
        std::cerr << "Unable to create mpg123 handle" << std::endl;
        mpg123_exit();
        return 1;
    }
    int err = mpg123_open(mh, argv[1]);
    if(err != MPG123_OK) {
        printf("Failed to open file: %s\n", mpg123_strerror(mh));
        mpg123_close(mh);
        mpg123_delete(mh);
        mpg123_exit();
        return 1;
    }
    if (mpg123_open(mh, "C:\\Users\\HP\\Desktop\\Mock\\test.mp3") != MPG123_OK) {
        std::cerr << "Unable to open file" << std::endl;
        mpg123_close(mh);
        mpg123_delete(mh);
        mpg123_exit();
        return 1;
    }

    // Lấy thời lượng bài hát (đơn vị: giây)
    off_t length = mpg123_length(mh);
    double duration = (double)length / mpg123_tpf(mh);
    std::cout << "Duration: " << duration << " seconds" << std::endl;
    long rate;
    int channels, encoding;
    mpg123_getformat(mh, &rate, &channels, &encoding);
    printf("Rate: %liHz, Channels: %i, Encoding: %i\n", rate, channels, encoding);

    int meta_flags = mpg123_meta_check(mh);
    if(meta_flags & MPG123_NEW_ID3) {
        err = mpg123_id3(mh, &id3v1, &id3v2);
        if(err == MPG123_OK) {
            printf("Title: %s\n", id3v2->title ? id3v2->title->p : "Unknown");
            printf("Artist: %s\n", id3v2->artist ? id3v2->artist->p : "Unknown");
            printf("Album: %s\n", id3v2->album ? id3v2->album->p : "Unknown");
            printf("Year: %s\n", id3v2->year ? id3v2->year->p : "Unknown");
            printf("Genre: %s\n", id3v2->genre ? id3v2->genre->p : "Unknown");
        }
    }

    if(meta_flags & MPG123_NEW_ICY) {
        err = mpg123_icy(mh, &icy_meta);
        if(err == MPG123_OK) {
            printf("ICY Metadata: %s\n", icy_meta ? icy_meta : "None");
        }
    }

    // Đóng tệp
    mpg123_close(mh);
    mpg123_delete(mh);

    // Giải phóng libmpg123
    mpg123_exit();

    return 0;
}