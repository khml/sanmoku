#include "../src/Board.hpp"
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

namespace py = pybind11;

class PyBoard
{
public:
    PyBoard()
    { board = Board(); };

    virtual ~PyBoard()
    {};

    void put(const int pos, const bool isCross)
    {
        if (isCross)
            board.put(pos, CROSS);
        else
            board.put(pos, CYCLE);
    };

    bool isLegal(const int pos)
    {
        return board.isLegal(pos) > 0;
    };

    bool isFinished()
    {
        return board.isFinished() > 0;
    };

    py::array_t<int> asList()
    {
        int* array = board.asList();
        py::array_t<int> pyArray(BOARD_SIZE);
        for(int i=0; i<BOARD_SIZE; i++)
        {
            *pyArray.mutable_data(i) = array[i];
        }
        return pyArray;
    };

    int result()
    {
        return board.result;
    };

private:
    Board board;
};

PYBIND11_MODULE(ccsanmoku, m)
{
    m.doc() = "Python Sanmoku Module implemented by C++";
    py::class_<PyBoard>(m,"Board")
        .def(py::init())
        .def("put", &PyBoard::put, "put(const int pos, const bool isCross)")
        .def("asList", &PyBoard::asList)
        .def("isLegal", &PyBoard::isLegal, "isLegal(const int pos)")
        .def("isFinished", &PyBoard::isFinished)
        .def("result", &PyBoard::result);
}
