#include "Context.h"
#include "Project.h"

#include <QDebug>
#include <QSettings>

Context::Context() : project_(nullptr)
{
  qDebug() << "Loading settings";
  QSettings settings;
  showMachineCode_ = settings.value("Context.showMachineCode", true).toBool();
  disassemblerSyntax_ = static_cast<Disassembler::Syntax>(
    settings.value("Context.disassemblerSyntax", static_cast<int>(Disassembler::Syntax::INTEL))
      .toInt());
}

Context::~Context()
{
  qDebug() << "Saving settings";
  QSettings settings;
  settings.setValue("Context.showMachineCode", showMachineCode());
  settings.setValue("Context.disassemblerSyntax", static_cast<int>(disassemblerSyntax()));
}

Context &Context::get()
{
  static Context instance;
  return instance;
}

bool Context::showMachineCode() const
{
  return showMachineCode_;
}

void Context::setShowMachineCode(bool show)
{
  bool changed = (show != showMachineCode_);
  showMachineCode_ = show;
  if (changed) {
    emit showMachineCodeChanged(show);
  }
}

Disassembler::Syntax Context::disassemblerSyntax() const
{
  return disassemblerSyntax_;
}

void Context::setDisassemblerSyntax(Disassembler::Syntax syntax)
{
  disassemblerSyntax_ = syntax;
}

std::shared_ptr<Project> Context::project() const
{
  return project_;
}

std::shared_ptr<Project> Context::resetProject()
{
  if (project_) {
    project_.reset();
  }

  project_ = std::make_shared<Project>();
  return project_;
}
