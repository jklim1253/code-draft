#include <iostream>
#include <string>
#include <algorithm>
#include <list>
#include <map>
#include <sstream>
using namespace std;

struct handler
{
public :
    struct management
    {
        void push(const string& key, handler* p)
        {
            depot.insert({ key, p });
        }
        handler* operator[](const string& key)
        {
            static handler error_handler("_error_");

            auto it = depot.find(key);
            if (it == depot.end())
                return &error_handler;

            return it->second;
        }
        management() {}
        ~management() {}
        map<string, handler*> depot;
    };

public :
    static management manager;
    handler(const string& key) : errorbit(true)
    {
        manager.push( key, this );

        errorbit = false;
    }
    virtual handler& operator()(bool& stop, const list<string>& tokens)
    {
        cout << "unknown keyword";
        return *this;
    }
    friend ostream& operator << (ostream& os, const handler& obj)
    {
        obj.result(os);
        return os;
    }
    virtual void result(ostream& os) const
    {

    }
    operator bool()
    {
        return (false || !errorbit);
    }

    bool errorbit;
};
handler::management handler::manager;

list<string> tokenizer(const string& src, const string& delimiter = " ")
{
    bool need_to_item = true;
    list<string> result;
    for (auto c : src)
    {
        if (any_of(begin(delimiter), end(delimiter), [c](string::value_type _c) { return c == _c; }))
        {
            need_to_item = true;
        }
        else
        {
            if (need_to_item)
            {
                need_to_item = false;
                result.push_back(string());
            }

            result.back().push_back(c);
        }
    }

    return result;
}

handler* parse_command_line(const list<string>& tokens)
{
    return handler::manager[tokens.front()];
}

void register_handlers();

int main()
{
    register_handlers();

    bool manual_stop = false;
    while (!manual_stop)
    {
        string line;
        handler* handle = nullptr;
        do
        {
            cout << "$ ";
            getline(cin, line);
            if (line.empty()) continue;

            list<string> tokens = tokenizer(line);
            handle = parse_command_line(tokens);

            cout << ((*handle)(manual_stop, tokens)) << endl;

        } while (line.empty() || (*handle));
    }

    return 0;
}

// handler implementation
struct handle_quit : public handler
{
    handle_quit() : handler("quit") {}
    virtual handler& operator()(bool& stop, const list<string>& tokens) override
    {
        stop = true;
        this->errorbit = true;
        return *this;
    }
    virtual void result(ostream& os) const override
    {
        os << "bye";
    }
};
struct handle_plus : public handler
{
    handle_plus() : handler("+") {}
    virtual handler& operator()(bool& stop, const list<string>& tokens) override
    {
        auto second = tokens.begin();
        advance(second, 1);

        value = 0;
        for_each(second, end(tokens), [&](auto token) {
            int item;
            stringstream ss(token);
            ss >> item;
            value += item;
        });

        return *this;
    }
    virtual void result(ostream& os) const override
    {
        os << value;
    }

    int value;
};

struct handle_minus : public handler
{
    handle_minus() : handler("-") {}
    virtual handler& operator()(bool& stop, const list<string>& tokens) override
    {
        auto second = tokens.begin();
        advance(second, 1);

        int lhs;
        stringstream ss(*second);
        ss >> lhs;

        auto third = second;
        advance(third, 1);

        value = lhs;
        for_each(third, end(tokens), [&](auto token) {
            int item;
            stringstream ss(token);
            ss >> item;
            value -= item;
        });

        return *this;
    }
    virtual void result(ostream& os) const override
    {
        os << value;
    }

    int value;
};

struct handle_multiply : public handler
{
    handle_multiply() : handler("*") {}
    virtual handler& operator()(bool& stop, const list<string>& tokens) override
    {
        auto second = tokens.begin();
        advance(second, 1);

        value = 1;
        for_each(second, end(tokens), [&](auto token) {
            int item;
            stringstream ss(token);
            ss >> item;
            value *= item;
        });

        return *this;
    }
    virtual void result(ostream& os) const override
    {
        os << value;
    }

    int value;
};


void register_handlers()
{
    static handle_quit _quit;
    static handle_plus _plus;
    static handle_minus _minus;
    static handle_multiply _multiply;
}
