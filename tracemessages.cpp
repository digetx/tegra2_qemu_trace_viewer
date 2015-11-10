#include "tracemessages.h"

TraceMessages::TraceMessages(QWidget *parent) :
    TraceQTableWidget(0, 1, parent)
{
    setHorizontalHeaderLabels(QStringList() << "Messages");
}

void TraceMessages::insertMessage(char *msg)
{
    int next_row = rowCount();

    insertRow(next_row);

    setItem(next_row, 0, new QTableWidgetItem(QString(msg)));
}
