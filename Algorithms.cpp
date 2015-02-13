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
