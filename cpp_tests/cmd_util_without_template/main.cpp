#include <QCoreApplication>
#include <QHash>
#include <iostream>
#include <stdexcept>


class FnArg {
public:
    FnArg(const QString &textArg) : m_textArg(textArg) {}

    int toInt() const
    {
        bool ok = false;
        const int result = m_textArg.toInt(&ok);
        if (!ok) {
            throw std::logic_error("cannot convert argument to int");
        }

        return result;
    }

    float toFloat() const
    {
        bool ok = false;
        const float result = m_textArg.toFloat(&ok);
        if (!ok) {
            throw std::logic_error("cannot convert argument to float");
        }

        return result;
    }

    // любые другие касты

private:
    // опережая вопросы любителей const в членах классов:
    // используется контейнер QList которому необходим оператор '='
    QString m_textArg;
};


class FnContainer {
public:
    typedef void (*Func)(const QList<FnArg> &args);

    FnContainer() {}

    void add(const QString &alias, Func fn)
    {
        m_fnHash.insert(alias, fn);
    }

    void call(const QString &alias, const QList<FnArg> &args)
    {
        if (!m_fnHash.contains(alias)) {
            throw std::logic_error("alias not registered");
        }

        m_fnHash.value(alias)(args);
    }

private:
    QHash<QString, Func> m_fnHash;
};


void sumInt(const QList<FnArg> &args)
{
    int sum = 0.0;
    foreach (const FnArg &arg, args) {
        sum += arg.toInt();
    }

    std::cout << "sum = " << sum << std::endl;
}


void sumFloat(const QList<FnArg> &args)
{
    float sum = 0.0;
    foreach (const FnArg &arg, args) {
        sum += arg.toFloat();
    }

    std::cout << "sum = " << sum << std::endl;
}

int main(int argc, char *argv[])
{    
    QCoreApplication app(argc, argv);
    if (app.arguments().count() < 2) {
        std::cout << "Usage: app_name cmd_alias <args ...>" << std::endl;
        return EXIT_FAILURE;
    }

    FnContainer fnContainer;
    fnContainer.add("sum_int", sumInt);
    fnContainer.add("sum_float", sumFloat);

    QList<FnArg> fnArgs;
    foreach (const QString &arg, app.arguments().mid(2)) {
        fnArgs.append(FnArg(arg));
    }

    try {
        fnContainer.call(app.arguments().at(1), fnArgs);
    }
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

// Результат:
// $ ./app_name sum_int
// sum = 0
// $ ./app_name sum_float 10 20
// sum = 30
// $ ./app_name sum_float 10 1.5
// sum = 11.5
// $ ./app_name sum_int 1.5 3
// cannot convert argument to int
// $ ./app_name sum_int2 1.5 3
// alias not registered
