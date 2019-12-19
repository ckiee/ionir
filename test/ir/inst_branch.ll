; ModuleID = 'test'
source_filename = "test"

define void @foobar() {
entry:

ifbody:                                           ; preds = %ifbody
  br i1 false, label %ifbody, <null operand!>
}
