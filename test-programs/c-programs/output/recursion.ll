; ModuleID = '../recursion.c'
source_filename = "../recursion.c"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@.str = private unnamed_addr constant [11 x i8] c"fib is %d\0A\00", align 1

; Function Attrs: noinline nounwind optnone
define void @fib(i32 %x, i32 %y) #0 {
  %x.addr = alloca i32, align 4
  %y.addr = alloca i32, align 4
  store i32 %x, i32* %x.addr, align 4
  store i32 %y, i32* %y.addr, align 4
  %1 = load i32, i32* %x.addr, align 4
  %cmp = icmp eq i32 %1, 1
  br i1 %cmp, label %2, label %4

; <label>:2:                                      ; preds = %0
  %3 = load i32, i32* %y.addr, align 4
  %add = add nsw i32 %3, 1
  store i32 %add, i32* %y.addr, align 4
  br label %9

; <label>:4:                                      ; preds = %0
  %5 = load i32, i32* %y.addr, align 4
  %add1 = add nsw i32 %5, 1
  store i32 %add1, i32* %y.addr, align 4
  %6 = load i32, i32* %x.addr, align 4
  %sub = sub nsw i32 %6, 1
  %7 = load i32, i32* %y.addr, align 4
  call void @fib(i32 %sub, i32 %7)
  %8 = load i32, i32* %y.addr, align 4
  %call = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str, i32 0, i32 0), i32 %8)
  br label %9

; <label>:9:                                      ; preds = %4, %2
  ret void
}

declare i32 @printf(i8*, ...) #1

; Function Attrs: noinline nounwind optnone
define void @main() #0 {
  %y = alloca i32, align 4
  store i32 0, i32* %y, align 4
  %1 = load i32, i32* %y, align 4
  call void @fib(i32 10, i32 %1)
  ret void
}

attributes #0 = { noinline nounwind optnone "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-features"="+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-features"="+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 6.0.1-svn334776-1~exp1~20180919141756.113 (branches/release_60)"}
