#include "CStringReader.h"

CStringReader::CStringReader(const QByteArray &data) : data(data), pos(0)
{
}

bool CStringReader::next()
{
  auto size = data.size();
  if (pos == size - 1) return false;

  // Clear when trying to read next string, and jump over the \0.
  if (!string_.isEmpty()) {
    string_.clear();
    pos++;
  }

  for (; pos < size; pos++) {
    int ch = data[pos];
    if (ch == 0) break;
    string_.append((char) ch);
  }

  return !string_.isEmpty();
}

QString CStringReader::string() const
{
  return string_;
}

QStringList CStringReader::readAll()
{
  QStringList res;
  while (next()) {
    res << string();
  }
  return res;
}
