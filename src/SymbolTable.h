#ifndef BMOD_SYMBOL_TABLE_H
#define BMOD_SYMBOL_TABLE_H

#include "SymbolEntry.h"

#include <QList>
#include <QString>

class SymbolTable {
public:
  void addSymbol(const SymbolEntry &entry);
  QList<SymbolEntry> &symbols();
  const QList<SymbolEntry> &symbols() const;

  bool string(quint64 value, QString &str) const;

private:
  QList<SymbolEntry> entries;
};

#endif // BMOD_SYMBOL_TABLE_H
