#pragma once

#include <string>

#include "cExpr.h"
#include "cVarRef.h"
#include "cSymbol.h"

class cAddressExpr : public cExpr
{
  public:
    cAddressExpr(cExpr *expr) : cExpr() 
    {
        cVarRef *var = dynamic_cast<cVarRef*>(expr);
        if (var == NULL)
            ThrowSemanticError("Took the address of something that isn't a var");
        AddChild(expr);
    }

    virtual cTypeDecl *GetType() { return GetVar()->GetType(); }

    cVarRef* GetVar() { return (cVarRef*)GetChild(0); }


    virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
