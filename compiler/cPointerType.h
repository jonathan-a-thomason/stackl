#pragma once

#include <string>

#include "cTypeDecl.h"
#include "cSymbol.h"
#include "../interp/machine_def.h"

class cPointerType : public cTypeDecl
{
  public:
    cPointerType(cSymbol *name) : cTypeDecl(name, WORD_SIZE)
    {
        name->SetDecl(this);
        symbolTableRoot->InsertRoot(name);
    }

    virtual cTypeDecl *ParentType() 
    {
        std::string name = GetName()->Name();

        // remove the last "*"
        name.pop_back();

        cSymbol *sym = symbolTableRoot->Lookup(name);
        if (sym == NULL) fatal_error("Pointer type with no base type.");

        return dynamic_cast<cTypeDecl*>(sym->GetDecl());
    }

    virtual bool IsPointer() { return true; }

    // FIX THIS: need this overload?
    virtual int  ElementSize() { return ParentType()->Size(); }

    virtual void GenerateCode()
    {}

    static cPointerType *PointerType(cTypeDecl *base)
    {
        std::string name = base->GetName()->Name() + "*";
        cSymbol *sym = symbolTableRoot->Lookup(name);
        if (sym == NULL) 
        {
            sym = new cSymbol(name);
            return new cPointerType(sym);
        } else {
            return dynamic_cast<cPointerType *>(sym->GetDecl());
        }

        return NULL;
    }

    virtual string NodeType()             { return "PointerType"; }
    virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }

};

