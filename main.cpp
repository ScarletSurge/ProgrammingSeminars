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

class tkey final {};

class tvalue final
{
private:
    std::string _1 = "12345";
    std::string _2 = "kek";
    int _3;
};



class tkey_comparer final
{

public:

    int operator()(
        tkey const &key1,
        tkey const &key2) const
    {
        return rand() % 3 - 1;
    }

};

class db_server final
{

public:

    enum class mode
    {
        uninitialized,
        in_memory_cache,
        file_system
    };

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

        search_tree<tkey, tvalue> *_data;
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
                    _data = new b_tree<tkey, tvalue>(t_for_b_trees, tkey_comparer());
                    break;
            }
        }

    private:

        void clear()
        {
            delete _data;
            _data = nullptr;
        }

        void copy_from(
            collection const &other)
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
                    _data = new b_tree<tkey, tvalue>(
                        *dynamic_cast<b_tree<tkey, tvalue> *>(other._data));
                    break;
            }
        }

        void move_from(
            collection &&other)
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
                    _data = new b_tree<tkey, tvalue>(
                        std::move(*dynamic_cast<b_tree<tkey, tvalue> *>(other._data)));
                    break;
            }
        }

    public:

        ~collection()
        {
            clear();
        }

        collection(
            collection const &other)
        {
            copy_from(other);
        }

        collection &operator=(
            collection const &other)
        {
            if (this != &other)
            {
                clear();
                copy_from(other);
            }

            return *this;
        }

        collection(
            collection &&other) noexcept
        {
            move_from(std::move(other));
        }

        collection &operator=(
            collection &&other) noexcept
        {
            if (this != &other)
            {
                clear();
                move_from(std::move(other));
            }

            return *this;
        }

    public:

        void insert(
            tkey const &key,
            tvalue const &value)
        {
            _data->insert(key, value);
        }

        void insert(
            tkey const &key,
            tvalue &&value)
        {
            _data->insert(key, std::move(value));
        }

        void update(
            tkey const &key,
            tvalue const &value)
        {
            _data->update(key, value);
        }

        void update(
            tkey const &key,
            tvalue &&value)
        {
            _data->update(key, std::move(value));
        }

        tvalue &obtain(
            tkey const &key)
        {
            return _data->obtain(key);
        }

        tvalue dispose(
            tkey const &key)
        {
            return _data->dispose(key);
        }

        std::vector<typename associative_container<tkey, tvalue>::key_value_pair> obtain_between(
            tkey const &lower_bound,
            tkey const &upper_bound,
            bool lower_bound_inclusive,
            bool upper_bound_inclusive)
        {
            return _data->obtain_between(lower_bound, upper_bound, lower_bound_inclusive, upper_bound_inclusive);
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
            search_tree_variant variant,
            size_t t_for_b_trees = 8)
        {
            _collections->insert(collection_name, collection(variant, t_for_b_trees));
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
            search_tree_variant variant,
            size_t t_for_b_trees = 8)
        {
            _schemas->insert(schema_name, schema(variant, t_for_b_trees));
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

    // static db_server *_instance;
    // static std::mutex _sync_object;
    b_tree<std::string, pool> _pools;
    mode _mode;

public:

    static db_server *get_instance()
    {
        // if (_instance == nullptr)
        // {
        //     std::lock_guard<std::mutex> lock(_sync_object);
        //     if (_instance == nullptr)
        //     {
        //         _instance = new db_server();
        //     }
        // }
        //
        // return _instance;

        static auto *instance = new db_server();
        return instance;
    }

private:

    db_server():
        _pools(8, stdstring_comparer()),
        _mode(mode::uninitialized)
    {

    }

public:

    db_server(
        db_server const &) = delete;

    db_server(
        db_server &&) = delete;

private:

    void add(
        std::string const &pool_name,
        search_tree_variant variant,
        size_t t_for_b_trees = 8)
    {
        _pools.insert(pool_name, pool(variant, t_for_b_trees));
    }

    pool &obtain(
        std::string const &pool_name)
    {
        if (_mode == mode::file_system)
        {
            fseek
            // TODO: check existence of path
        }
        return _pools.obtain(pool_name);
    }

    void dispose(
        std::string const &pool_name)
    {
        _pools.dispose(pool_name);
    }

public:

    void add_pool(
        std::string const &pool_name,
        search_tree_variant variant,
        size_t t_for_b_trees = 8)
    {
        throw_if_uninitialized_at_perform()
            .add(pool_name, variant, t_for_b_trees);
    }

    void dispose_pool(
        std::string const &pool_name)
    {
        throw_if_uninitialized_at_perform()
            .dispose(pool_name);
    }

    void add_schema(
        std::string const &pool_name,
        std::string const &schema_name,
        search_tree_variant variant,
        size_t t_for_b_trees = 8)
    {
        throw_if_uninitialized_at_perform()
            .obtain(pool_name)
            .add(schema_name, variant, t_for_b_trees);
    }

    void dispose_schema(
        std::string const &pool_name,
        std::string const &schema_name)
    {
        throw_if_uninitialized_at_perform()
            .obtain(pool_name)
            .dispose(schema_name);
    }

    void add_collection(
        std::string const &pool_name,
        std::string const &schema_name,
        std::string const &collection_name,
        search_tree_variant variant,
        size_t t_for_b_trees = 8)
    {
        throw_if_uninitialized_at_perform()
            .throw_if_invalid_path(pool_name)
            .throw_if_invalid_path(schema_name)
            .throw_if_invalid_file_name(collection_name)
            .throw_if_path_is_too_long(pool_name, schema_name, collection_name)
            .obtain(pool_name)
            .obtain(schema_name)
            .add(collection_name, variant, t_for_b_trees);
    }

    void dispose_collection(
        std::string const &pool_name,
        std::string const &schema_name,
        std::string const &collection_name)
    {
        throw_if_uninitialized_at_perform()
            .obtain(pool_name)
            .obtain(schema_name)
            .dispose(collection_name);
    }

    void add(
        std::string const &pool_name,
        std::string const &schema_name,
        std::string const &collection_name,
        tkey const &key,
        tvalue const &value)
    {
        throw_if_uninitialized_at_perform()
            .obtain(pool_name)
            .obtain(schema_name)
            .obtain(collection_name)
            .insert(key, value);
    }

    void add(
        std::string const &pool_name,
        std::string const &schema_name,
        std::string const &collection_name,
        tkey const &key,
        tvalue &&value)
    {
        throw_if_uninitialized_at_perform()
            .obtain(pool_name)
            .obtain(schema_name)
            .obtain(collection_name)
            .insert(key, std::move(value));
    }

    void update(
        std::string const &pool_name,
        std::string const &schema_name,
        std::string const &collection_name,
        tkey const &key,
        tvalue const &value)
    {
        throw_if_uninitialized_at_perform()
            .obtain(pool_name)
            .obtain(schema_name)
            .obtain(collection_name)
            .update(key, value);
    }

    void update(
        std::string const &pool_name,
        std::string const &schema_name,
        std::string const &collection_name,
        tkey const &key,
        tvalue &&value)
    {
        throw_if_uninitialized_at_perform()
            .obtain(pool_name)
            .obtain(schema_name)
            .obtain(collection_name)
            .update(key, std::move(value));
    }

    tvalue &obtain(
        std::string const &pool_name,
        std::string const &schema_name,
        std::string const &collection_name,
        tkey const &key)
    {
        return throw_if_uninitialized_at_perform()
            .obtain(pool_name)
            .obtain(schema_name)
            .obtain(collection_name)
            .obtain(key);
    }

    std::vector<typename associative_container<tkey, tvalue>::key_value_pair> obtain_between(
        std::string const &pool_name,
        std::string const &schema_name,
        std::string const &collection_name,
        tkey const &lower_bound,
        tkey const &upper_bound,
        bool lower_bound_inclusive,
        bool upper_bound_inclusive)
    {
        return throw_if_uninitialized_at_perform()
            .obtain(pool_name)
            .obtain(schema_name)
            .obtain(collection_name)
            .obtain_between(lower_bound, upper_bound, lower_bound_inclusive, upper_bound_inclusive);
    }

    void dispose(
        std::string const &pool_name,
        std::string const &schema_name,
        std::string const &collection_name,
        tkey const &key)
    {
        throw_if_uninitialized_at_perform()
            .obtain(pool_name)
            .obtain(schema_name)
            .obtain(collection_name)
            .dispose(key);
    }

private:

    db_server &throw_if_uninutialized(
        mode mode,
        std::string const &exception_message)
    {
        if (mode != mode::uninitialized)
        {
            return *this;
        }

        throw std::logic_error(exception_message);
    }

    db_server &throw_if_uninitialized_at_setup(
        mode mode)
    {
        return throw_if_uninutialized(mode, "invalid mode");
    }

    db_server &throw_if_initialized_at_setup()
    {
        if (_mode == mode::uninitialized)
        {
            return *this;
        }

        throw std::logic_error("attempt to change previously set up mode");
    }

    db_server &throw_if_uninitialized_at_perform()
    {
        return throw_if_uninutialized(_mode, "attempt to perform an operation while mode not initialized");
    }

public:

    db_server *set_mode(
        mode mode)
    {
        throw_if_initialized_at_setup()
            .throw_if_uninitialized_at_setup(mode);

        _mode = mode;

        return this;
    }

private:

    db_server &throw_if_invalid_path(
        std::string const &subpath)
    {
        if (_mode == mode::file_system)
        {
            // TODO: you can do it O_o
        }

        return *this;
    }

    db_server &throw_if_invalid_file_name(
        std::string const &file_name)
    {
        if (_mode == mode::file_system)
        {
            // TODO: you can do it O_o
        }

        return *this;
    }

    db_server &throw_if_path_is_too_long(
        std::string const &pool_name,
        std::string const &schema_name,
        std::string const &collection_name)
    {
        if (_mode == mode::file_system)
        {
            // TODO: you can do it O_o
        }

        return *this;
    }

};

// db_server *db_server::_instance = nullptr;

int main(
    int argc,
    char *argv[])
{
    db_server::get_instance()
        ->set_mode(db_server::mode::in_memory_cache)
        ->set_mode(db_server::mode::file_system)
        ->add_pool("", db_server::search_tree_variant::b, 3);

    return 0;
}