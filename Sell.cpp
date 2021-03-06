#include "Sell.h"

Sell::Sell(MYSQL m_) {
    m = m_;
}

bool Sell::find_book() {
    return 1;
}

int Sell::get_inventory() {
    string sql = "select * from book where bid='";
    sql += bid;
    sql += "'";
    
    if (mysql_query(&m, sql.c_str()) == 0) {
        MYSQL_RES *res = mysql_store_result(&m);
        if (res) {
            MYSQL_ROW row = mysql_fetch_row(res);
            stringstream ss;
            int num = 0;
            ss << row[2];
            ss >> num;
            return num;
        }
    }
    return 0;
}

void Sell::update_book_table() {
    string sql = "update book b set b.bnum = b.bnum-1 where b.bid='";
    sql += bid;
    sql += "'";
    if (mysql_query(&m, sql.c_str()) != 0) {
        printf("query fail!\n");
    }
}

void Sell::update_sell_table() {
    string sql = "insert into sell(cid, bid, sdate) values('";
    sql += cid;
    sql += "','";
    sql += bid;
    sql += "','";
    sql += date;
    sql += "')";
    cout << sql << endl;
    if (mysql_query(&m, sql.c_str()) != 0) {
        cout << mysql_error(&m) << endl;
    }
}

void Sell::print_sell_list() {
    cout << "---------------------------------" << endl;
    cout << "日期：" << date << endl; 
    cout << "顾客id:" << cid << "顾客名字:" << endl;
    cout << "书籍号:" << bid << "书籍名:" << endl;
    cout << "---------------------------------" << endl;
}

bool Sell::sell(string bid, string cid, string date) {
    set_values(bid, cid, date);
    int num = get_inventory();
    if (num) {
        cout << "库存量：" << num << endl;
        update_book_table();
        update_sell_table();
        print_sell_list();
    }
    else {
        cout << "该书已卖完" << endl;
    }
    return true;
}