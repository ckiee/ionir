template <typename TResult, typename TVisitor>
class Visitable
{
public:
    virtual TResult accept(TVisitor visitor) = 0;
};
