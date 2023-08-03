#include <iostream>
#include <string>
using namespace std;

// Tạo liên kết đôi thành 1 playlist để lưu trữ các bài hát
struct music
{
    string name_song;
    int time;
    music *pre;
    music *next;
};

struct playlist
{
    string playlist_name;
    music *head;
};

// Hàm lấy ra giá trị nguyên ngẫu nhiên giá trị trong khoảng từ min đến max
int int_rand(int min, int max)
{
    return min + rand() % (max + 1 - min);
}

// Tạo ra 1 playlist với tên được truyền vào
playlist *createPlaylist(string playlist_created_name, string song_created_name)
{
    playlist *p = new playlist;
    p->head = new music;
    p->head->name_song = song_created_name;
    p->head->time = int_rand(180, 240);
    p->playlist_name = playlist_created_name;
    p->head->next = NULL;
    p->head->pre = NULL;
    return p;
}

// Thêm bài hát vào đầu playlist
playlist *add_Song(playlist *p, string name_added_song)
{

    music *new_added_song = new music;           // Tạo 1 bài hát mới
    new_added_song->name_song = name_added_song; // Gán tên bài hát được truyền vào bài hát vừa được tạo trong playlist
    new_added_song->time = int_rand(180, 240);   // Tạo thời gian của bài hát
    new_added_song->pre = NULL;                  // Con trỏ pre sẽ trỏ tới NULL do ở đầu playlist
    new_added_song->next = p->head;              // con trỏ next trỏ tới con trỏ head của playlist
    p->head->pre = new_added_song;               // con trỏ pre của con trỏ head trỏ tới bài hát vừa mới tạo
    p->head = new_added_song;                    // cho con trỏ head trỏ tới bài hát đầu
    return p;
}

// IN ra danh sách các bài hát trong playlist
void print_playlist(playlist *p)

{
    music *l = p->head;
    while (l != NULL)
    {
        cout << l->name_song << " " << endl;
        l = l->next;
    }
}

// Xóa 1 bài hát trong playlist
playlist *deleteSong(playlist *p, string name_deleted_song)
{
    music *cur = p->head;
    while (cur)
    {
        // Case 1 : Playlist rỗng
        if (p->head == NULL)
            cout << "Playlist cua ban chua co bai hat nao ca" << endl;
        else
        {
            if (cur->name_song == name_deleted_song && cur == p->head)
            {
                // Case 2 : Playlist có 1 bài hát duy nhất
                if (cur->next == NULL)
                {
                    p->head = NULL;
                    delete (cur);
                    return p;
                }
                // Case 3 : Playlist có nhiều bài hát và bát hát muốn xóa ở đầu
                else
                {
                    music *next = p->head->next;
                    cur->next = NULL;
                    next->pre = NULL;
                    p->head = next;
                    delete (cur);
                    return p;
                }
            }
            else
            {
                if (cur->name_song == name_deleted_song)
                {
                    // Case 4: Playlist có nhiều bài hát và bài hát muốn xóa ở giữa
                    if (cur->next)
                    {
                        music *next = cur->next;
                        music *pre = cur->pre;
                        pre->next = next;
                        next->pre = pre;
                        cur->next = NULL;
                        cur->pre = NULL;
                        delete (cur);
                        return p;
                    }
                    // Case 5 : Playlist có nhiều bài và bài muốn xóa ở cuối
                    else
                    {
                        music *pre = cur->pre;
                        pre->next = NULL;
                        cur->pre = NULL;
                        delete (cur);
                        return p;
                    }
                }
            }
        }
        cur = cur->next;
    }
    cout << "Bai hat ban muon xoa khong ton tai" << endl;
    return p;
}

// Tạo danh sách các bài hát đã nghe
playlist *create_list_of_played_song(music *song_played)
{
    playlist *list_played_song = new playlist;
    list_played_song->head = new music;
    list_played_song->head->name_song = song_played->name_song;
    list_played_song->head->time = song_played->time;
    list_played_song->head->next = NULL;
    list_played_song->head->pre = NULL;
    return list_played_song;
}

// Hàm thêm bài đã nghe vào danh sách các bài hát đã nghe
playlist *add_played_song(playlist *list_played_song, music *song_played)
{
    music *new_added_song = new music;
    new_added_song->name_song = song_played->name_song;
    new_added_song->time = song_played->time;
    new_added_song->pre = NULL;
    new_added_song->next = list_played_song->head;
    list_played_song->head->pre = new_added_song;
    list_played_song->head = new_added_song;
    return list_played_song;
}

// Hàm in ra danh sách các bài hát đã nghe
void print_playlist_with_time_input(playlist *p, int time)
{
    music *temp = p->head;
    int i = 1;
    while (temp)
    {
        cout << i << "." << temp->name_song << endl;
        time = time - temp->time;
        if (time <= 0)
            break;
        i++;
        temp = temp->next;
    }
}

// Tạo liên kết đơn để lữu trữ các playlist
struct list_of_playlist
{
    playlist *list;
    list_of_playlist *next;
};

list_of_playlist *create_list_of_playlist(playlist *p)
{
    list_of_playlist *l = new list_of_playlist;
    l->list = p;
    l->next = NULL;
    return l;
}

list_of_playlist *add_playlist(playlist *adding_playlist, list_of_playlist *l)
{
    list_of_playlist *p = l;
    while (p->next != NULL)
    {
        p = p->next;
    }
    list_of_playlist *temp = new list_of_playlist;
    temp->list = adding_playlist;
    temp->next = NULL;
    p->next = temp;
    return l;
}

void print_list_of_playlist(list_of_playlist *l)
{
    list_of_playlist *cur = l;
    while (cur)
    {
        cout << cur->list->playlist_name << endl;
        cur = cur->next;
    }
}

playlist *access_playlist(list_of_playlist *l, string access_playlist, int &n)
{
    list_of_playlist *cur = l;
    if (cur == NULL)
    {
        cout << "Ban khong co playlist nao" << endl;
        return NULL;
    }
    else
    {
        while (cur)
        {
            if (cur->list->playlist_name == access_playlist)
            {
                print_playlist(cur->list);
                break;
            }
            cur = cur->next;
            if (!cur)
            {
                cout << "Playlist ban nhap khong ton tai" << endl;
                n = 0;
                return NULL;
            }
        }
    }
    return cur->list;
}

// Hàm chơi nhạc
music *Play(playlist *p, string name_playing_song, int &d)
{
    music *cur = p->head;
    if (p->head == NULL)
    {
        cout << "Ban khong co bai hat nao de nghe" << endl;
        return NULL;
    }
    else
    {
        while (cur)
        {
            if (cur->name_song == name_playing_song)
            {
                cout << "Playing " << cur->name_song << "...." << endl;
                cout << cur->time << endl;
                break;
            }
            cur = cur->next;
            if (!cur)
            {
                cout << "Bai hat ban muon nghe khong ton tai" << endl;
                d = 0;
            }
        }
    }
    return cur;
}

// Hiển thị menu
void menu()
{
    cout << "---------------Mp3 Player-------------" << endl;
    cout << "1. Tao 1 playlist moi" << endl;
    cout << "2. Them bai hat" << endl;
    cout << "3. Xoa bai hat" << endl;
    cout << "4. Hien thi cac playlist" << endl;
    cout << "5. Nghe nhac" << endl;
    cout << "6. Cac bai hat da nghe" << endl;
    cout << "7. Thoat chuong trinh" << endl;
}

// Chọn các chức năng trong menu
void chonMenu()
{
    list_of_playlist *l = NULL;
    playlist *p = NULL;
    playlist *list_played_song = NULL;
    char a;
    do
    {
        cout << "Chon chuc nang" << endl;
        cin >> a;
        cin.ignore();
        switch (a)
        {
        case '1': // Tạo 1 playlist mới
        {
            print_list_of_playlist(l); // In ra các playlist hiện có
            cout << "Nhap ten playlist ban muon tao: ";
            string name_playlist_want_to_create;
            getline(cin, name_playlist_want_to_create);
            cout << "Nhap bai hat ma ban muon them vao: ";
            string name_song_want_to_add;
            getline(cin, name_song_want_to_add);
            playlist *new_playlist = createPlaylist(name_playlist_want_to_create, name_song_want_to_add);
            p = new_playlist;
            if (l == NULL)
            {
                l = create_list_of_playlist(p);
            }
            else
            {
                l = add_playlist(p, l);
            }
            cout << "Danh sach hien tai co cac bai la: " << endl;
            print_playlist(p);
            if (p->playlist_name == name_playlist_want_to_create)
                cout << "Ban da tao playlist thanh cong" << endl;
            system("pause");
            break;
        }
        case '2': // Thêm bài hát vào playlist mong muốn
        {
            if (l == NULL)
            {
                cout << "Ban chua co 1 playlist nao" << endl;
                break;
            }
            cout << "Cac playlist hien co" << endl;
            print_list_of_playlist(l);
            cout << "Nhap ten playlist ma ban muon them bai hat: ";
            string name_playlist_want_to_access;
            getline(cin, name_playlist_want_to_access);
            int n = 1;
            playlist *temp = access_playlist(l, name_playlist_want_to_access, n);
            if (n == 0)
                break;
            else
            {
                cout << "Nhap bai hat ban muon them: ";
                string name_song_want_to_add;
                getline(cin, name_song_want_to_add);
                temp = add_Song(temp, name_song_want_to_add);
                if (temp->head->name_song == name_song_want_to_add)
                    cout << "Ban da them bai hat thanh cong" << endl;
                cout << "playlist hien tai cua ban co bai: " << endl;
                print_playlist(temp);
                break;
            }
        }
        case '3': // Xóa bài hát khỏi playlist mong muốn
        {
            if (l == NULL)
            {
                cout << "Ban chua co 1 playlist nao" << endl;
                break;
            }
            cout << "Cac playlist hien co" << endl;
            print_list_of_playlist(l);
            cout << "Nhap ten playlist ma ban muon xoa bai hat: ";
            string name_playlist_want_to_access;
            getline(cin, name_playlist_want_to_access);
            int n = 1;
            playlist *temp = access_playlist(l, name_playlist_want_to_access, n);
            if (n == 0)
                break;
            else
            {
                cout << "Nhap ten bai hat ban muon xoa: ";
                string name_song_want_to_delete;
                getline(cin, name_song_want_to_delete);
                temp = deleteSong(temp, name_song_want_to_delete);
                cout << endl;
                cout << "Playlist cua ban hien tai: " << endl;
                print_playlist(temp);
                break;
            }
        }
        case '4': // In ra các playlist hiện tại
        {
            if (l == NULL)
            {
                cout << "Khong co playlist nao" << endl;
                break;
            }
            print_list_of_playlist(l);
            break;
        }
        case '5': // Chọn bài hát để nghe
        {
            if (l == NULL)
            {
                cout << "Khong co bai hat nao de nghe" << endl;
                break;
            }
            print_list_of_playlist(l);
            cout << "Nhap ten playlist ban muon truy cap:";
            string playlist_want_to_access;
            getline(cin, playlist_want_to_access);
            int n = 1;
            playlist *temp = access_playlist(l, playlist_want_to_access, n);
            if (n == 0)
                break;
            else
            {
                cout << "Nhap ten bai hat ban muon nghe:";
                string name_song_want_to_listen;
                getline(cin, name_song_want_to_listen);
                int d = 1;
                music *song = Play(temp, name_song_want_to_listen, d);
                if (d)
                {
                    if (list_played_song == NULL)
                    {
                        list_played_song = create_list_of_played_song(song);
                    }
                    else
                    {
                        list_played_song = add_played_song(list_played_song, song);
                    }
                    cout << endl;
                    char kitu;
                    do
                    {
                        cout << "1.Chuyen bai tiep theo" << endl;
                        cout << "2.Chuyen ve bai truoc" << endl;
                        cout << "3.Ket thuc nghe nhac" << endl;
                        cin >> kitu;
                        switch (kitu)
                        {
                        case '1':
                        {
                            if (song->next == NULL)
                            {
                                cout << "Khong co bai hat tiep theo" << endl;
                                break;
                            }
                            else
                            {
                                song = Play(temp, song->next->name_song, d);
                                list_played_song = add_played_song(list_played_song, song);
                                break;
                            }
                        }
                        case '2':
                        {
                            if (song->pre == NULL)
                            {
                                cout << "Khong co bai hat truoc do" << endl;
                                break;
                            }
                            else
                            {
                                song = Play(temp, song->pre->name_song, d);
                                list_played_song = add_played_song(list_played_song, song);
                                break;
                            }
                        }
                        case '3':
                        {
                            cout << "Ket thuc nghe nhac..." << endl;
                            break;
                        }
                        }
                    } while (kitu != '3');
                }
                break;
            }
        }
        case '6': // Hiển thị các bài hát đã nghe theo thời gian vừa nhập tính theo đơn vị giây
        {
            if (list_played_song == NULL)
            {
                cout << "Ban chua nghe bai hat nao" << endl;
                break;
            }
            cout << "Nhap thoi gian: ";
            int time;
            cin >> time;
            print_playlist_with_time_input(list_played_song, time);
            system("pause");
            break;
        }
        case '7': // Kết thúc chương trình
        {
            cout << "Cam on ban da su dung phan mem" << endl;
            break;
        }
        }
        cout << endl;
    } while (a != '7');
}

int main()
{
    menu();
    chonMenu();
    return 0;
}