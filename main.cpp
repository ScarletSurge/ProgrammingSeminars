#include <exception>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <optional>
#include <stack>
#include <utility>
#include <vector>

class serializable
{

public:

    virtual ~serializable() noexcept = default;

public:

    virtual void serialize(
        std::ostream &stream) const = 0;

    virtual void deserialize(
        std::istream &stream) = 0;

};

template<
    typename tkey,
    typename tvalue>
class associative_container
{

public:

    struct key_value_pair final
    {

    public:

        tkey key;
        tvalue value;

    public:

        key_value_pair(
            tkey const &key,
            tvalue const &value):
            key(key),
            value(value)
        {

        }

        key_value_pair(
            tkey const &key,
            tvalue &&value):
            key(key),
            value(std::move(value))
        {

        }

    };

    struct key_value_ptr_pair
    {

    public:

        tkey key;
        tvalue *value_ptr;

    public:

        key_value_ptr_pair(
            tkey const &key,
            tvalue *value_ptr):
            key(key),
            value_ptr(value_ptr)
        {

        }

    };

public:

    virtual ~associative_container() noexcept = default;

public:

    virtual size_t elements_count() const = 0;

public:

    virtual void insert(
        tkey const &key,
        tvalue const &value) = 0;

    virtual void insert(
        tkey const &key,
        tvalue &&value) = 0;

    virtual void update(
        tkey const &key,
        tvalue const &value) = 0;

    virtual void update(
        tkey const &key,
        tvalue &&value) = 0;

    virtual tvalue &obtain(
        tkey const &key) = 0;

    virtual tvalue dispose(
        tkey const &key) = 0;

};

template<
    typename tkey,
    typename tvalue>
class search_tree:
    public associative_container<tkey, tvalue>
{

public:

    virtual std::vector<typename associative_container<tkey, tvalue>::key_value_pair> obtain_between(
        tkey const &lower_bound,
        tkey const &upper_bound,
        bool lower_bound_inclusive,
        bool upper_bound_inclusive) = 0;

};

template<
    typename tkey,
    typename tvalue>
class b_tree final:
    public search_tree<tkey, tvalue>
{

public:

    class node final
    {
        // TODO: здесь могла бы быть Ваша реклама =)
    };

    class iterator final
    {

    private:

        std::stack<node *> _path;

    public:

        explicit iterator(
            std::stack<node *> const &path):
                _path(path)
        {
            // TODO: ?!
        }

        iterator &operator++()
        {
            // TODO: impl

            return *this;
        }

        iterator operator++(
            int)
        {
            auto this_copy = *this;
            ++*this;
            return this_copy;
        }

        bool operator==(
            iterator const &other) const
        {
            return !(*this != other);
        }

        bool operator!=(
            iterator const &other) const
        {
            return !(*this == other);
        }

        std::tuple<tkey, tvalue &, size_t, size_t> operator*()
        {
            // TODO: unmock
            return std::make_tuple(tkey(), tvalue(), 0, 0);
        }

    };

    class iterator_const final
    {

    private:

        iterator _inner;

    public:

        explicit iterator_const(
            std::stack<node *> const &path):
                _inner(path)
        {
            // TODO: ?!
        }

        iterator_const &operator++()
        {
            ++_inner;

            return *this;
        }

        iterator_const operator++(
            int)
        {
            auto this_copy = *this;
            ++*this;
            return this_copy;
        }

        bool operator==(
            iterator_const const &other) const
        {
            return !(*this != other);
        }

        bool operator!=(
            iterator_const const &other) const
        {
            return !(*this == other);
        }

        std::tuple<tkey, tvalue const &, size_t, size_t> operator*()
        {
            // TODO: unmock
            return std::make_tuple(tkey(), tvalue(), 0, 0);
        }

    };

private:

    size_t _elements_count;

public:

    b_tree(
        size_t t,
        std::function<int(tkey const &, tkey const &)> comparer):
            _elements_count(0)
    {
        throw std::exception(); // "not_implemented"
    }

public:

    void insert(
        tkey const &key,
        tvalue const &value) override
    {
        throw std::exception();

        ++_elements_count;
    }

    void insert(
        tkey const &key,
        tvalue &&value) override
    {
        throw std::exception();

        ++_elements_count;
    }

    void update(
        tkey const &key,
        tvalue const &value) override
    {
        throw std::exception();
    }

    void update(
        tkey const &key,
        tvalue &&value) override
    {
        throw std::exception();
    }

    tvalue &obtain(
        tkey const &key) override
    {
        throw std::exception();
    }

    tvalue dispose(
        tkey const &key) override
    {
        throw std::exception();

        --_elements_count;
    }

    std::vector<typename associative_container<tkey, tvalue>::key_value_pair> obtain_between(
        tkey const &lower_bound,
        tkey const &upper_bound,
        bool lower_bound_inclusive,
        bool upper_bound_inclusive) override
    {
        throw std::exception();
    }

public:

    size_t elements_count() const override
    {
        return _elements_count;
    }

public:

    iterator begin() const
    {
        std::stack<node *> path;
        // TODO: initialize stack

        return iterator(path);
    }

    iterator end() const
    {
        return iterator(std::stack<node *>());
    }

    iterator_const cbegin() const
    {
        std::stack<node *> path;
        // TODO: initialize stack

        return iterator_const(path);
    }

    iterator_const cend() const
    {
        return iterator_const(std::stack<node *>());
    }

};

class strings_flyweight_container final
{

private:

    struct string_flyweight final
    {

        friend class strings_flyweight_container;

    private:

        std::string _value;

    public:

        string_flyweight(
            std::string &&value):
                _value(std::move(value))
        {

        }

    public:

        string_flyweight(
            string_flyweight const &) = delete;

        string_flyweight &operator=(
            string_flyweight const &) = delete;

        string_flyweight(
            string_flyweight &&) = delete;

        string_flyweight &operator=(
            string_flyweight &&) = delete;

    public:

        [[nodiscard]] std::string const &get_string() const
        {
            return _value;
        }

    };

public:

    static strings_flyweight_container *get_instance()
    {
        auto *instance = new strings_flyweight_container();
        return instance;
    }

private:

    std::map<std::string const *, string_flyweight> _flyweights;

private:

    strings_flyweight_container() = default;

public:

    strings_flyweight_container(
        strings_flyweight_container const &) = delete;

    strings_flyweight_container &operator=(
        strings_flyweight_container const &) = delete;

    strings_flyweight_container(
        strings_flyweight_container &&) = delete;

    strings_flyweight_container &operator=(
        strings_flyweight_container &&) = delete;

public:

    string_flyweight const &get(
        std::string const &key)
    {
        auto it = _flyweights.find(&key);

        if (it != _flyweights.end())
        {
            return it->second;
        }

        // extra parentheses, to provide constructor call instead of function declaration

        string_flyweight v((std::string(key)));
        auto k = &v._value;

        // TODO: fix this
        //_flyweights.emplace(std::make_pair(k, v));
        return v;
    }

};

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

class tkey final:
    serializable
{

public:

    void serialize(
        std::ostream &stream) const override
    {
        stream << "key serialize mock" << std::endl;
    }

    void deserialize(
        std::istream &stream) override
    {
        std::string str;
        stream >> str;
    }

};

class tvalue final:
    serializable
{

public:

    std::string _1 = "12345";
    std::string _2 = "kek";
    int _3;

public:

    void serialize(
        std::ostream &stream) const override
    {
        stream << "value serialize mock" << std::endl;
    }

    void deserialize(
        std::istream &stream) override
    {
        std::string str;
        stream >> str;
    }

};

class tdata final:
    serializable
{

public:

    tkey key;
    tvalue value;

public:

    void serialize(
        std::ostream &stream) const override
    {
        key.serialize(stream);
        value.serialize(stream);
    }

    void deserialize(
        std::istream &stream) override
    {
        key.deserialize(stream);
        value.deserialize(stream);
    }

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

class db_server final:
    serializable
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

    class chain_of_responsibility;

    class collection final
    {

    public:

        enum class iterator_initial_state
        {
            begin,
            end
        };

        class input_iterator final
        {

        public:

            //input_iterator(


        };

        class output_iterator final
        {

        public:

            output_iterator(
                search_tree<std::string &, search_tree<tdata, std::vector<chain_of_responsibility>> *> *data,
                iterator_initial_state initial_state)
            {

            }

        };

    private:

        // tdata { int, str, binary }
        // 3. search_tree<std::string, search_tree<tdata, CoR> *> *

        search_tree<std::string &, search_tree<tdata, std::vector<chain_of_responsibility>> *> *_data;
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
                    //_data = new b_tree<tkey, tvalue>(t_for_b_trees, tkey_comparer());
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
                    //_data = new b_tree<tkey, tvalue>(
                       // *dynamic_cast<b_tree<tkey, tvalue> *>(other._data));
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
                   // _data = new b_tree<tkey, tvalue>(
                     //   std::move(*dynamic_cast<b_tree<tkey, tvalue> *>(other._data)));
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
            //_data->insert(key, value);
        }

        void insert(
            tkey const &key,
            tvalue &&value)
        {
            //_data->insert(key, std::move(value));
        }

        void update(
            tkey const &key,
            tvalue const &value)
        {
            //_data->update(key, value);
        }

        void update(
            tkey const &key,
            tvalue &&value)
        {
            //_data->update(key, std::move(value));
        }

        tvalue &obtain(
            tkey const &key)
        {
            //return _data->obtain(key);
        }

        tvalue dispose(
            tkey const &key)
        {
            //return _data->dispose(key);
        }

        std::vector<typename associative_container<tkey, tvalue>::key_value_pair> obtain_between(
            tkey const &lower_bound,
            tkey const &upper_bound,
            bool lower_bound_inclusive,
            bool upper_bound_inclusive)
        {
            //return _data->obtain_between(lower_bound, upper_bound, lower_bound_inclusive, upper_bound_inclusive);
        }

    public:

        [[nodiscard]] input_iterator ibegin() const
        {
            return input_iterator(/**/);
        }

        [[nodiscard]] input_iterator iend() const
        {
            return input_iterator(/**/);
        }

        [[nodiscard]] output_iterator obegin() const
        {
            return output_iterator(_data, iterator_initial_state::begin);
        }

        [[nodiscard]] output_iterator oend() const
        {
            return output_iterator(_data, iterator_initial_state::end);
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

    class pool final:
        serializable
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

    public:

        void serialize(
            std::ostream &stream) const override
        {
            auto elements_count = _schemas->elements_count();
            stream << elements_count;
            for (auto it = _schemas.cbegin(); it != _schemas.cend(); ++it)
            {
                auto const key_value_pair_state = *it;
                stream << std::get<0>(key_value_pair_state)
                       << std::get<2>(key_value_pair_state)
                       << std::get<3>(key_value_pair_state);
                std::get<1>(key_value_pair_state).serialize(stream);
            }

            // TODO: implement this using scheme from db_server::serialize implementation
        }

        void deserialize(
            std::istream &stream) override
        {
            // TODO: implement this using scheme from db_server::deserialize implementation
        }

    };

private:

    class command:
        public serializable
    {

    public:

        virtual ~command() noexcept = default;

    public:

        virtual void execute(
            bool &data_exists,
            std::optional<tdata> &data_to_modify) const = 0;

    };

    class insert_command final:
        public command
    {

    private:

        tdata _initial_version;

    public:

        explicit insert_command(
            tdata &&initial_version):
                _initial_version(initial_version)
        {

        }

    public:

        void execute(
            bool &data_exists,
            std::optional<tdata> &data_to_modify) const override
        {
            if (data_exists)
            {
                throw std::logic_error("attempt to insert already existent data");
            }

            if (data_to_modify.has_value())
            {
                data_to_modify.value() = _initial_version;
            }

            data_exists = true;
        }

    public:

        void serialize(
            std::ostream &stream) const override
        {
            stream << 'i';
            _initial_version.serialize(stream);
        }

        void deserialize(
            std::istream &stream) override
        {
            char c;
            stream >> c;
            if (c != 'i')
            {
                // TODO: throw an exception (deserialization error)
            }
            _initial_version.deserialize(stream);
        }

    };

    class update_command final:
        public command
    {

    private:

        std::string _update_expression;

    public:

        explicit update_command(
            std::string const &update_expression):
                _update_expression(update_expression)
        {

        }

    public:

        void execute(
            bool &data_exists,
            std::optional<tdata> &data_to_modify) const override
        {
            if (!data_exists)
            {
                throw std::logic_error("attempt to modify non-existent data");
            }

            if (data_to_modify.has_value())
            {
                // TODO: interpreter for update expression
            }
        }

    public:

        void serialize(
            std::ostream &stream) const override
        {
            stream << 'u' << _update_expression;
        }

        void deserialize(
            std::istream &stream) override
        {
            char c;
            stream >> c;
            if (c != 'u')
            {
                // TODO: throw an exception (deserialization error)
            }
            stream >> _update_expression;
        }

    };

    class dispose_command final:
        public command
    {

    public:

        void execute(
            bool &data_exists,
            std::optional<tdata> &data_to_modify) const override
        {
            if (!data_exists)
            {
                throw std::logic_error("attempt to dispose non-existent data");
            }

            data_exists = false;
        }

    public:

        void serialize(
            std::ostream &stream) const override
        {
            stream << 'd';
        }

        void deserialize(
            std::istream &stream) override
        {
            char c;
            stream >> c;
            if (c != 'd')
            {
                // TODO: throw an exception (deserialization error)
            }
        }

    };

private:

    class chain_of_responsibility_handler final:
        serializable
    {

        friend class chain_of_responsibility;

    private:

        command *_command;
        std::int64_t _date_time_activity_started;
        chain_of_responsibility_handler *_next_handler;

    public:

        chain_of_responsibility_handler(
            command *command,
            std::int64_t date_time_activity_started):
                _command(command),
                _date_time_activity_started(date_time_activity_started),
                _next_handler(nullptr)
        {

        }

    public:

        void handle(
            bool &data_exists,
            std::optional<tdata> &data_to_modify,
            std::int64_t date_time_target) const
        {
            if (date_time_target <= _date_time_activity_started)
            {
                return;
            }

            _command->execute(data_exists, data_to_modify);

            if (_next_handler != nullptr)
            {
                _next_handler->handle(data_exists, data_to_modify, date_time_target);
            }
        }

    public:

        void serialize(
            std::ostream &stream) const override
        {
            _command->serialize(stream);
            stream << _date_time_activity_started;
        }

        void deserialize(
            std::istream &stream) override
        {
            // TODO: are there any already allocated resources;
            _command->deserialize(stream);
            stream >> _date_time_activity_started;
        }

    };

    class chain_of_responsibility final:
        serializable
    {

    private:

        chain_of_responsibility_handler *_first_handler;
        chain_of_responsibility_handler *_last_handler;

    public:

        chain_of_responsibility():
            _first_handler(nullptr),
            _last_handler(nullptr)
        {

        }

    private:

        void add_handler(
            command *command)
        {
            // TODO: obtain date/time from OS
            // TODO: convert date/time from OS to std::int64_t
            std::int64_t date_time_activity_started = 0;

            auto *added_handler = new chain_of_responsibility_handler(command, date_time_activity_started);

            if (_last_handler == nullptr)
            {
                _first_handler = _last_handler = added_handler;
            }
            else
            {
                _last_handler->_next_handler = added_handler;
                _last_handler = added_handler;
            }
        }

        void handle(
            bool &data_exists,
            std::optional<tdata> &data_to_modify,
            std::int64_t date_time_target)
        {
            if (_first_handler == nullptr)
            {
                return;
            }

            _first_handler->handle(data_exists, data_to_modify, date_time_target);
        }

    public:

        void insert(
            tdata &&data_to_insert)
        {
            bool data_exists = false;
            std::optional<tdata> empty_optional;
            // TODO: obtain date/time from OS
            // TODO: convert date/time from OS to std::int64_t
            std::int64_t current_date_time = 0;
            handle(data_exists, empty_optional, current_date_time);

            if (data_exists)
            {
                throw std::logic_error("attempt to add data insertion handler while data exists");
            }

            add_handler(new insert_command(std::move(data_to_insert)));
        }

        std::optional<tdata> obtain(
            std::int64_t date_time_of_activity)
        {
            bool data_exists;
            tdata data_to_modify;
            auto data_to_modify_optional = std::make_optional(data_to_modify);

            handle(data_exists, data_to_modify_optional, date_time_of_activity);

            return data_exists
                ? std::make_optional(std::move(data_to_modify))
                : std::optional<tdata>();
        }

        void update(
            tdata const &data,
            std::string const &update_expression)
        {
            bool data_exists = false;
            std::optional<tdata> empty_optional;
            // TODO: obtain date/time from OS
            // TODO: convert date/time from OS to std::int64_t
            std::int64_t current_date_time = 0;
            handle(data_exists, empty_optional, current_date_time);

            if (!data_exists)
            {
                throw std::logic_error("attempt to add data update handler while data not exists");
            }

            add_handler(new update_command(update_expression));
        }

        void dispose(
            tdata const &data)
        {
            bool data_exists = false;
            std::optional<tdata> empty_optional;
            // TODO: obtain date/time from OS
            // TODO: convert date/time from OS to std::int64_t
            std::int64_t current_date_time = 0;
            handle(data_exists, empty_optional, current_date_time);

            if (!data_exists)
            {
                throw std::logic_error("attempt to add data dispose handler while data not exists");
            }

            add_handler(new dispose_command);
        }

    public:

        void serialize(
            std::ostream &stream) const override
        {
            // TODO: this is not good ._.
            size_t chain_size = 0;
            auto *current = _first_handler;
            while (current != nullptr)
            {
                ++chain_size;
                current = current->_next_handler;
            }
            stream << chain_size;

            current = _first_handler;
            while (current != nullptr)
            {
                current->serialize(stream);
                current = current->_next_handler;
            }
        }

        void deserialize(
            std::istream &stream) override
        {
            // TODO: dispose old state
            _first_handler = _last_handler = nullptr;

            size_t chain_size;
            stream >> chain_size;

            for (auto i = 0; i != chain_size; ++i)
            {
                if (_first_handler == nullptr)
                {
                    _first_handler = _last_handler = new chain_of_responsibility_handler(nullptr, 0);
                    _first_handler->deserialize(stream);
                }
                else
                {
                    _last_handler->_next_handler = new chain_of_responsibility_handler(nullptr, 0);
                    _last_handler = _last_handler->_next_handler;
                    _last_handler->deserialize(stream);
                }
            }
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
            // fseek
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

    db_server *add_pool(
        std::string const &pool_name,
        search_tree_variant variant,
        size_t t_for_b_trees = 8)
    {
        throw_if_uninitialized_at_perform()
            .add(pool_name, variant, t_for_b_trees);

        return this;
    }

    db_server *dispose_pool(
        std::string const &pool_name)
    {
        throw_if_uninitialized_at_perform()
            .dispose(pool_name);

        return this;
    }

    db_server *add_schema(
        std::string const &pool_name,
        std::string const &schema_name,
        search_tree_variant variant,
        size_t t_for_b_trees = 8)
    {
        throw_if_uninitialized_at_perform()
            .obtain(pool_name)
            .add(schema_name, variant, t_for_b_trees);

        return this;
    }

    db_server *dispose_schema(
        std::string const &pool_name,
        std::string const &schema_name)
    {
        throw_if_uninitialized_at_perform()
            .obtain(pool_name)
            .dispose(schema_name);

        return this;
    }

    db_server *add_collection(
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

        return this;
    }

    db_server *dispose_collection(
        std::string const &pool_name,
        std::string const &schema_name,
        std::string const &collection_name)
    {
        throw_if_uninitialized_at_perform()
            .obtain(pool_name)
            .obtain(schema_name)
            .dispose(collection_name);

        return this;
    }

    db_server *add(
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

        return this;
    }

    db_server *add(
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

        return this;
    }

    db_server *update(
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

        return this;
    }

    db_server *update(
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

        return this;
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

    db_server *dispose(
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

        return this;
    }

public:

    void serialize(
        std::ostream &stream) const override
    {
        auto elements_count = _pools.elements_count();
        stream << elements_count;
        for (auto it = _pools.cbegin(); it != _pools.cend(); ++it)
        {
            auto const key_value_pair_state = *it;
            stream << std::get<0>(key_value_pair_state)
                   << std::get<2>(key_value_pair_state)
                   << std::get<3>(key_value_pair_state);
            std::get<1>(key_value_pair_state).serialize(stream);
        }
    }

    db_server const *serialize(
        std::string const &file_path) const
    {
        std::ofstream stream(file_path);
        if (!stream.is_open())
        {
            // TODO: throw an exception
        }

        serialize(stream);

        return this;
    }

    void deserialize(
        std::istream &stream) override
    {

    }

    db_server *deserialize(
        std::string const &file_path)
    {
        std::ifstream stream(file_path);
        if (!stream.is_open())
        {
            // TODO: throw an exception
        }

        return this;
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
        ->add_pool("pool", db_server::search_tree_variant::b, 3)
        ->add_schema("pool", "schema", db_server::search_tree_variant::b, 5)
        ->add_collection("pool", "schema", "collection", db_server::search_tree_variant::b, 6);

    return 0;
}