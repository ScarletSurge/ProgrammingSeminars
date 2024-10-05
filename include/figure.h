#ifndef PROGRAMMINGSEMINARS_FIGURE_H
#define PROGRAMMINGSEMINARS_FIGURE_H

class figure //final
{

public:

    struct point
    {

    public:

        double x;
        double y;

    };

public:

    virtual ~figure() = default;

public:

    virtual point mass_center() const = 0;

    virtual explicit operator double() const = 0;

    friend std::ostream &operator<<(
        std::ostream &stream,
        figure const *obj);

    friend std::istream &operator>>(
        std::istream &stream,
        figure *obj);

protected:

    virtual std::ostream &print(
        std::ostream &stream) const = 0;

    virtual std::istream &read(
        std::istream &stream) = 0;

};

#endif //PROGRAMMINGSEMINARS_FIGURE_H