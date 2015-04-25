#pragma once

#include <string>
#include <list>
using std::list;

#include "cAstNode.h"
#include "cExprNode.h"
#include "cAstList.h"
#include "cStructDeclNode.h"
#include "cArrayValNode.h"
#include "cVarDeclNode.h"
#include "cSymbolTable.h"
#include "cVarPartNode.h"

#include "parse.h"
#include "codegen.h"

class cVarDerefNode : public cExprNode
{
  public:
    cVarDerefNode(cVarRefNode *var) 
    {
        mVar = var;
        mOffset = 0;
    }

    cDeclNode *GetType()
    {
        return mVar->GetType();
    }

    virtual int ComputeOffsets(int base)
    {
        mVar->ComputeOffsets(base);
        mOffset = mVar->GetOffset();
        return base;
    }

    virtual std::string toString()
    {
        std::string result = "&";
        result += mVar->toString();

        return result;
    }

    virtual void GenerateCode()
    {
        EmitInt(PUSHVAR_OP);
        EmitInt(mOffset);
        EmitInt(PUSHVARIND_OP);
    }

  protected:
    cVarRefNode *mVar;
    int mOffset;
};

