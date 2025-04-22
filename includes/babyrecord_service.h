#ifndef BABY_RECORD_STORE_H
#define BABY_RECORD_STORE_H

#include <sqlite3.h>


// Basic CRUD operations
void add_cd(sqlite3* db, const char* title, const char* manufacturer, 
const char* release_date, float price, int quantity);
void add_song(sqlite3* db, const char* song_name, const char* author, 
const char* performer, int cd_id);
void add_transaction(sqlite3* db, const char* date, float amount, const 
char* type, int cd_id, int user_id);
void add_user(sqlite3* db, const char* name, const char* email, const 
char* phone);
void update_cd(sqlite3* db, int id, const char* title, const char* 
manufacturer, const char* release_date, float price, int quantity);
void delete_cd(sqlite3* db, int id);

// Reporting functions
void get_cd_inventory(sqlite3* db);  // Shows sold vs remaining CDs sorted 
by difference
void get_cd_sales_period(sqlite3* db, int cd_id, const char* start_date, 
const char* end_date);  // Sales for specific CD in period
void get_most_popular_cd(sqlite3* db);  // Info about most frequently 
bought CD and its songs
void get_most_popular_performer(sqlite3* db);  // Sales info for most 
popular performer
void get_author_sales(sqlite3* db);  // Sales statistics by author

// Special functions
void validate_sale(sqlite3* db, int cd_id, int quantity);  // Prevents 
overselling (req #4)
void generate_period_report(sqlite3* db, const char* start_date, const 
char* end_date);  // Creates period report table (req #5)
void get_cd_sales_report(sqlite3* db, int cd_id, const char* start_date, 
const char* end_date);  // Detailed CD sales report (req #6)

#endif // BABY_RECORD_STORE_H
