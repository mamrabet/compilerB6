// Fichier Algorithms.cpp
#include "Algorithms.h"
VirtualInstruction* DominationTask::findDominatorWith(VirtualInstruction& source) const {
      int thisHeight = m_height-1;
      VirtualInstruction *thisInstruction = m_previous, *sourceInstruction = &source;
      int sourceHeight = sourceInstruction->getDominationHeight();
          while (thisHeight > sourceHeight) {
             assert(thisInstruction);
            if (thisInstruction->countPreviouses() == 1)
              thisInstruction = thisInstruction->getSPreviousInstruction();

           else {
               assert(dynamic_cast<const LabelInstruction*>(thisInstruction));
              thisInstruction = dynamic_cast<const LabelInstruction*>(thisInstruction)->getSDominator();
                };
        thisHeight = thisInstruction->getDominationHeight();
        };
         while (sourceHeight > thisHeight) {
        assert(sourceInstruction);
           if (sourceInstruction->countPreviouses() == 1)
               sourceInstruction = sourceInstruction->getSPreviousInstruction();
          else {
             assert(dynamic_cast<const LabelInstruction*>(sourceInstruction));
             sourceInstruction = dynamic_cast<const LabelInstruction*>(sourceInstruction)->getSDominator();
               };
           sourceHeight = sourceInstruction->getDominationHeight();
        };
       while (thisInstruction != sourceInstruction) {
       assert(thisInstruction && sourceInstruction);
          if (thisInstruction->countPreviouses() == 1)
             thisInstruction =thisInstruction->getSPreviousInstruction();
          else {
              assert(dynamic_cast<const LabelInstruction*>(thisInstruction));
              thisInstruction = dynamic_cast<const LabelInstruction*>(thisInstruction)->getSDominator();
          };
       if (sourceInstruction->countPreviouses() == 1)
          sourceInstruction = sourceInstruction->getSPreviousInstruction();
       else {
        assert(dynamic_cast<const LabelInstruction*>(sourceInstruction));
          sourceInstruction = dynamic_cast<const LabelInstruction*>(sourceInstruction)->getSDominator();
       };
      };
return thisInstruction;
}

bool
PhiInsertionTask::IsBefore::operator()(VirtualExpression* fst, VirtualExpression* snd) const {
if (fst->type() == snd->type()) {
if (fst->type() == VirtualExpression::TLocalVariable) {
assert(dynamic_cast<const LocalVariableExpression*>(fst)
&& dynamic_cast<const LocalVariableExpression*>(snd));
return ((const LocalVariableExpression&) *fst).getGlobalIndex()
< ((const LocalVariableExpression&) *snd).getGlobalIndex();
};
if (fst->type() == VirtualExpression::TParameter) {
assert(dynamic_cast<const ParameterExpression*>(fst)
&& dynamic_cast<const ParameterExpression*>(snd));
return ((const ParameterExpression&) *fst).getIndex()
< ((const ParameterExpression&) *snd).getIndex();
};
assert(dynamic_cast<const GlobalVariableExpression*>(fst)
&& dynamic_cast<const GlobalVariableExpression*>(snd));
return ((const GlobalVariableExpression&) *fst).getIndex()
< ((const GlobalVariableExpression&) *snd).getIndex();
};
return fst->type() > snd->type();
}
