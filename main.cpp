/*#include <stdio.h>
#include <ctype.h>
#include <malloc.h>
#include "stack.h"

int main(
    int argc,
    char *argv[])
{
    int i, depth = 0, status_code;
    char c, pc = ' ', buf[BUFSIZ], *b = buf, *initialization_mark = NULL;
    FILE *input_file;
    stack variables_stack;
    code_block_variable_info variable_info;
    stack_item *iterator;

    if (argc == 1)
    {
        printf("No input files passed!");
        return -1;
    }

    for (i = 1; i < argc; i++)
    {
        init_stack(&variables_stack);

        if (!(input_file = fopen(argv[i], "r")))
        {
            printf("Input file \"%s\" can't be opened!", argv[i]);

            continue;
        }

        while (!feof(input_file))
        {
            c = fgetc(input_file);

            if (c == '{')
            {
                ++depth;
            }
            else if (isalnum(c) || c == '=')
            {
                *b++ = c;
                if (c == '=')
                {
                    initialization_mark = b - 1;
                }
            }
            else if (c == '}')
            {
                do
                {
                    // TODO: check status_code validity
                    status_code = peek_stack(&variables_stack, &variable_info);
                    if (status_code == 3)
                    {
                        break;
                    }

                    free(variable_info.info.name);
                    variable_info.info.name = NULL;
                    if (depth == variable_info.depth)
                    {
                        // TODO: check status_code validity
                        status_code = pop_from_stack(&variables_stack, &variable_info);
                        free(variable_info.info.name);
                        variable_info.info.name = NULL;
                    }
                }
                while (depth == variable_info.depth);

                --depth;
            }
            else if (c == ';')
            {
                *b = '\0'; // = 0
                b = buf;

                if (initialization_mark == NULL)
                {
                    // ShowVar instruction handling
                    iterator = variables_stack.top;
                    while (iterator != NULL)
                    {
                        printf("\tName: \"%s\", value: %d\n", iterator->data.info.name, iterator->data.info.value);

                        iterator = iterator->next;
                    }
                    printf("\n");
                }
                else
                {
                    *initialization_mark++ = '\0';
                    // buf - variable name
                    // initialization_mark - variable value
                    variable_info.depth = depth;
                    if (sscanf(initialization_mark, "%d", &(variable_info.info.value)) != 1)
                    {
                        // TODO: handle parsing error
                    }
                    variable_info.info.name = buf;

                    // TODO: check status_code validity
                    status_code = push_into_stack(&variables_stack, &variable_info);

                    initialization_mark = NULL;
                }
            }

            pc = c;
        }

        fclose(input_file);
        destroy_stack(&variables_stack);
    }

    return 0;
}*/

#include <iostream>

#include "trie.h"

void print_trie(
    trie const &t)
{
    for (auto const &str: t.obtain_all())
    {
        std::cout << '\"' << str << '\"' << std::endl;
    }
}

void test_trie()
{
    trie t(std::set<char> { 'a', 'b', 'c', 'd', 'e' });
    //t.insert("");
    t.insert("aaa");
    t.insert("abc");
    t.insert("abcde");
    t.insert("bdec");
    t.insert("");
    t.insert("decd");

    trie t1 = t;

    std::cout << "t: " << std::endl; print_trie(t); std::cout << std::endl;
    std::cout << "t1: " << std::endl; print_trie(t1); std::cout << std::endl;

    t1.dispose("abc");
    t1.dispose("decd");
    t1.dispose("");

    std::cout << "t: " << std::endl; print_trie(t); std::cout << std::endl;
    std::cout << "t1: " << std::endl; print_trie(t1); std::cout << std::endl;

    t = std::move(t1);

    std::cout << "t: " << std::endl; print_trie(t); std::cout << std::endl;
    std::cout << "t1: " << std::endl; print_trie(t1); std::cout << std::endl;

    trie t2 = std::move(t);

    std::cout << "t: " << std::endl; print_trie(t); std::cout << std::endl;
    std::cout << "t1: " << std::endl; print_trie(t1); std::cout << std::endl;
    std::cout << "t2: " << std::endl; print_trie(t2); std::cout << std::endl;
}

#include <mutex>
#include "btree/b_tree.h"

class stdstring_comparer final
{

public:

    int operator()(
        std::string const &first,
        std::string const &second) const noexcept
    {
        if (first == second)
        {
            return 0;
        }

        if (first > second)
        {
            return 1;
        }

        return -1;
    }

};

class T final
{

public:

    std::string _name;
    std::string _surname;
    size_t _age;

public:

    class T_comparer1 final
    {

    private:

        stdstring_comparer _comparer;

    public:

        int operator()(
            T const *first,
            T const *second) const noexcept
        {
            return _comparer(first->_surname, second->_surname);
        }
    };

    class T_comparer2 final
    {

    private:

        stdstring_comparer _comparer;

    public:

        int operator()(
            T const *first,
            T const *second) const noexcept
        {
            if (first->_age > second->_age)
            {
                return first->_age - second->_age;
            }

            if (first->_age < second->_age)
            {
                auto result = second->_age - first->_age;
                return -*reinterpret_cast<int *>(&result);
            }

            return _comparer(first->_name, second->_name);
        }

    };

};

class db_server final
{

public:

    enum class search_tree_variant
    {
        AVL,
        red_black,
        splay,
        scapegoat,
        b,
        b_plus,
        b_star,
        b_star_plus
    };

private:

    class collection final
    {

    private:

        // std::variant
        search_tree<std::string, search_tree<T*, std::tuple<T**, size_t, size_t>> *> *_data;
        search_tree_variant _variant;

    public:

        explicit collection(
            search_tree_variant variant,
            size_t t_for_b_trees = 8):
                _variant(variant)
            {
                switch (variant)
                {
                    case search_tree_variant::AVL:
                    // _collections = new AVL_tree<std::string, schema>();
                    // break;
                    case search_tree_variant::red_black:
                    // _collections = new red_black_tree<std::string, schema>();
                    // break;
                    case search_tree_variant::splay:
                    // _collections = new splay_tree<std::string, schema>();
                    // break;
                    case search_tree_variant::scapegoat:
                    // _collections = new scapegoat_tree<std::string, schema>();
                    // break;
                    case search_tree_variant::b_plus:
                    // _collections = new b_plus<std::string, schema>();
                    // break;
                    case search_tree_variant::b_star:
                    // _collections = new b_star_tree<std::string, schema>();
                    // break;
                    case search_tree_variant::b_star_plus:
                    // _collections = new b_star_plus_tree<std::string, schema>();
                    // break;
                    case search_tree_variant::b:
                        //_data = new b_tree<tkey, tvalue>(t_for_b_trees, stdstring_comparer());
                    break;
                }
            }

    private:

        void clear()
        {
            delete _collections;
            _collections = nullptr;
        }

        void copy_from(
            schema const &other)
        {
            switch (_variant = other._variant)
            {
                case search_tree_variant::AVL:
                    // _schemas = new AVL_tree<std::string, schema>();
                    // break;
                case search_tree_variant::red_black:
                    // _schemas = new red_black_tree<std::string, schema>();
                    // break;
                case search_tree_variant::splay:
                    // _schemas = new splay_tree<std::string, schema>();
                    // break;
                case search_tree_variant::scapegoat:
                    // _schemas = new scapegoat_tree<std::string, schema>();
                    // break;
                case search_tree_variant::b_plus:
                    // _schemas = new b_plus<std::string, schema>();
                    // break;
                case search_tree_variant::b_star:
                    // _schemas = new b_star_tree<std::string, schema>();
                    // break;
                case search_tree_variant::b_star_plus:
                    // _schemas = new b_star_plus_tree<std::string, schema>();
                    // break;
                case search_tree_variant::b:
                    _collections = new b_tree<std::string, collection>(*dynamic_cast<b_tree<std::string, collection> *>(other._collections));
                    break;
            }
        }

        void move_from(
            schema &&other)
        {
            switch (_variant = other._variant)
            {
                case search_tree_variant::AVL:
                    // _schemas = new AVL_tree<std::string, schema>();
                    // break;
                case search_tree_variant::red_black:
                    // _schemas = new red_black_tree<std::string, schema>();
                    // break;
                case search_tree_variant::splay:
                    // _schemas = new splay_tree<std::string, schema>();
                    // break;
                case search_tree_variant::scapegoat:
                    // _schemas = new scapegoat_tree<std::string, schema>();
                    // break;
                case search_tree_variant::b_plus:
                    // _schemas = new b_plus<std::string, schema>();
                    // break;
                case search_tree_variant::b_star:
                    // _schemas = new b_star_tree<std::string, schema>();
                    // break;
                case search_tree_variant::b_star_plus:
                    // _schemas = new b_star_plus_tree<std::string, schema>();
                    // break;
                case search_tree_variant::b:
                    _collections = new b_tree<std::string, collection>(std::move(*dynamic_cast<b_tree<std::string, collection> *>(other._collections)));
                    break;
            }
        }

    public:

        ~schema()
        {
            clear();
        }

        schema(
            schema const &other)
        {
            copy_from(other);
        }

        schema &operator=(
            schema const &other)
        {
            if (this != &other)
            {
                clear();
                copy_from(other);
            }

            return *this;
        }

        schema(
            schema &&other) noexcept
        {
            move_from(std::move(other));
        }

        schema &operator=(
            schema &&other) noexcept
        {
            if (this != &other)
            {
                clear();
                move_from(std::move(other));
            }

            return *this;
        }

    public:

        void add(
            std::string const &collection_name,
            search_tree_variant variant)
        {
            _collections->insert(collection_name, collection(variant));
        }

        collection &obtain(
            std::string const &collection_name)
        {
            return _collections->obtain(collection_name);
        }

        void dispose(
            std::string const &collection_name)
        {
            _collections->dispose(collection_name);
        }

    };

    class schema final
    {

    private:

        search_tree<std::string, collection> *_collections;
        search_tree_variant _variant;

    public:

        explicit schema(
            search_tree_variant variant,
            size_t t_for_b_trees = 8):
            _variant(variant)
        {
            switch (variant)
            {
                case search_tree_variant::AVL:
                    // _collections = new AVL_tree<std::string, schema>();
                    // break;
                case search_tree_variant::red_black:
                    // _collections = new red_black_tree<std::string, schema>();
                    // break;
                case search_tree_variant::splay:
                    // _collections = new splay_tree<std::string, schema>();
                    // break;
                case search_tree_variant::scapegoat:
                    // _collections = new scapegoat_tree<std::string, schema>();
                    // break;
                case search_tree_variant::b_plus:
                    // _collections = new b_plus<std::string, schema>();
                    // break;
                case search_tree_variant::b_star:
                    // _collections = new b_star_tree<std::string, schema>();
                    // break;
                case search_tree_variant::b_star_plus:
                    // _collections = new b_star_plus_tree<std::string, schema>();
                    // break;
                case search_tree_variant::b:
                    _collections = new b_tree<std::string, collection>(t_for_b_trees, stdstring_comparer());
                    break;
            }
        }

    private:

        void clear()
        {
            delete _collections;
            _collections = nullptr;
        }

        void copy_from(
            schema const &other)
        {
            switch (_variant = other._variant)
            {
                case search_tree_variant::AVL:
                    // _schemas = new AVL_tree<std::string, schema>();
                    // break;
                case search_tree_variant::red_black:
                    // _schemas = new red_black_tree<std::string, schema>();
                    // break;
                case search_tree_variant::splay:
                    // _schemas = new splay_tree<std::string, schema>();
                    // break;
                case search_tree_variant::scapegoat:
                    // _schemas = new scapegoat_tree<std::string, schema>();
                    // break;
                case search_tree_variant::b_plus:
                    // _schemas = new b_plus<std::string, schema>();
                    // break;
                case search_tree_variant::b_star:
                    // _schemas = new b_star_tree<std::string, schema>();
                    // break;
                case search_tree_variant::b_star_plus:
                    // _schemas = new b_star_plus_tree<std::string, schema>();
                    // break;
                case search_tree_variant::b:
                    _collections = new b_tree<std::string, collection>(*dynamic_cast<b_tree<std::string, collection> *>(other._collections));
                    break;
            }
        }

        void move_from(
            schema &&other)
        {
            switch (_variant = other._variant)
            {
                case search_tree_variant::AVL:
                    // _schemas = new AVL_tree<std::string, schema>();
                    // break;
                case search_tree_variant::red_black:
                    // _schemas = new red_black_tree<std::string, schema>();
                    // break;
                case search_tree_variant::splay:
                    // _schemas = new splay_tree<std::string, schema>();
                    // break;
                case search_tree_variant::scapegoat:
                    // _schemas = new scapegoat_tree<std::string, schema>();
                    // break;
                case search_tree_variant::b_plus:
                    // _schemas = new b_plus<std::string, schema>();
                    // break;
                case search_tree_variant::b_star:
                    // _schemas = new b_star_tree<std::string, schema>();
                    // break;
                case search_tree_variant::b_star_plus:
                    // _schemas = new b_star_plus_tree<std::string, schema>();
                    // break;
                case search_tree_variant::b:
                    _collections = new b_tree<std::string, collection>(std::move(*dynamic_cast<b_tree<std::string, collection> *>(other._collections)));
                    break;
            }
        }

    public:

        ~schema()
        {
            clear();
        }

        schema(
            schema const &other)
        {
            copy_from(other);
        }

        schema &operator=(
            schema const &other)
        {
            if (this != &other)
            {
                clear();
                copy_from(other);
            }

            return *this;
        }

        schema(
            schema &&other) noexcept
        {
            move_from(std::move(other));
        }

        schema &operator=(
            schema &&other) noexcept
        {
            if (this != &other)
            {
                clear();
                move_from(std::move(other));
            }

            return *this;
        }

    public:

        void add(
            std::string const &collection_name,
            search_tree_variant variant)
        {
            _collections->insert(collection_name, collection(variant));
        }

        collection &obtain(
            std::string const &collection_name)
        {
            return _collections->obtain(collection_name);
        }

        void dispose(
            std::string const &collection_name)
        {
            _collections->dispose(collection_name);
        }

    };

    class pool final
    {

    private:

        search_tree<std::string, schema> *_schemas;
        search_tree_variant _variant;

    public:

        explicit pool(
            search_tree_variant variant,
            size_t t_for_b_trees = 8):
            _variant(variant)
        {
            switch (variant)
            {
                case search_tree_variant::AVL:
                    // _schemas = new AVL_tree<std::string, schema>();
                    // break;
                case search_tree_variant::red_black:
                    // _schemas = new red_black_tree<std::string, schema>();
                    // break;
                case search_tree_variant::splay:
                    // _schemas = new splay_tree<std::string, schema>();
                    // break;
                case search_tree_variant::scapegoat:
                    // _schemas = new scapegoat_tree<std::string, schema>();
                    // break;
                case search_tree_variant::b_plus:
                    // _schemas = new b_plus<std::string, schema>();
                    // break;
                case search_tree_variant::b_star:
                    // _schemas = new b_star_tree<std::string, schema>();
                    // break;
                case search_tree_variant::b_star_plus:
                    // _schemas = new b_star_plus_tree<std::string, schema>();
                    // break;
                case search_tree_variant::b:
                    _schemas = new b_tree<std::string, schema>(t_for_b_trees, stdstring_comparer());
                    break;
            }
        }

    private:

        void clear()
        {
            delete _schemas;
            _schemas = nullptr;
        }

        void copy_from(
            pool const &other)
        {
            switch (_variant = other._variant)
            {
                case search_tree_variant::AVL:
                    // _schemas = new AVL_tree<std::string, schema>();
                    // break;
                case search_tree_variant::red_black:
                    // _schemas = new red_black_tree<std::string, schema>();
                    // break;
                case search_tree_variant::splay:
                    // _schemas = new splay_tree<std::string, schema>();
                    // break;
                case search_tree_variant::scapegoat:
                    // _schemas = new scapegoat_tree<std::string, schema>();
                    // break;
                case search_tree_variant::b_plus:
                    // _schemas = new b_plus<std::string, schema>();
                    // break;
                case search_tree_variant::b_star:
                    // _schemas = new b_star_tree<std::string, schema>();
                    // break;
                case search_tree_variant::b_star_plus:
                    // _schemas = new b_star_plus_tree<std::string, schema>();
                    // break;
                case search_tree_variant::b:
                    _schemas = new b_tree<std::string, schema>(*dynamic_cast<b_tree<std::string, schema> *>(other._schemas));
                    break;
            }
        }

        void move_from(
            pool &&other)
        {
            switch (_variant = other._variant)
            {
                case search_tree_variant::AVL:
                    // _schemas = new AVL_tree<std::string, schema>();
                    // break;
                case search_tree_variant::red_black:
                    // _schemas = new red_black_tree<std::string, schema>();
                    // break;
                case search_tree_variant::splay:
                    // _schemas = new splay_tree<std::string, schema>();
                    // break;
                case search_tree_variant::scapegoat:
                    // _schemas = new scapegoat_tree<std::string, schema>();
                    // break;
                case search_tree_variant::b_plus:
                    // _schemas = new b_plus<std::string, schema>();
                    // break;
                case search_tree_variant::b_star:
                    // _schemas = new b_star_tree<std::string, schema>();
                    // break;
                case search_tree_variant::b_star_plus:
                    // _schemas = new b_star_plus_tree<std::string, schema>();
                    // break;
                case search_tree_variant::b:
                    _schemas = new b_tree<std::string, schema>(std::move(*dynamic_cast<b_tree<std::string, schema> *>(other._schemas)));
                    break;
            }
        }

    public:

        ~pool()
        {
            clear();
        }

        pool(
            pool const &other)
        {
            copy_from(other);
        }

        pool &operator=(
            pool const &other)
        {
            if (this != &other)
            {
                clear();
                copy_from(other);
            }

            return *this;
        }

        pool(
            pool &&other) noexcept
        {
            move_from(std::move(other));
        }

        pool &operator=(
            pool &&other) noexcept
        {
            if (this != &other)
            {
                clear();
                move_from(std::move(other));
            }

            return *this;
        }

    public:

        void add(
            std::string const &schema_name,
            search_tree_variant variant)
        {
            _schemas->insert(schema_name, schema(variant));
        }

        schema &obtain(
            std::string const &schema_name)
        {
            return _schemas->obtain(schema_name);
        }

        void dispose(
            std::string const &schema_name)
        {
            _schemas->dispose(schema_name);
        }

    };

private:

    static db_server *_instance;
    static std::mutex _sync_object;

public:

    static db_server *get_instance()
    {
        if (_instance == nullptr)
        {
            _sync_object.lock();
            if (_instance == nullptr)
            {
                _instance = new db_server();
            }
            _sync_object.unlock();
        }

        return _instance;
    }

private:

    db_server() = default;

public:

    db_server(
        db_server const &) = delete;

    db_server(
        db_server &&) = delete;

public:

    void foo()
    {

    }

    void bar()
    {

    }

};

db_server *db_server::_instance = nullptr;

int main(
    int argc,
    char *argv[])
{

    // test_trie();


    return 0;
}