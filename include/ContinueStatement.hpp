
#if !defined(ContinueStatement_hpp)
#define ContinueStatement_hpp

#include <Statement.hpp>


class ContinueStatement : public Statement {
  private:
    /* data */
  public:
    ContinueStatement(/* args */);
    virtual void accept(Visitor* visitor) { visitor->visit(this); }
    ~ContinueStatement();
};


#endif  // ContinueStatement_hpp
