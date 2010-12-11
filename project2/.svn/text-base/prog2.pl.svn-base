A
C
A
D
B
B
i
#!/usr/bin/perl -w
use strict;
package cs311;
#Torben Rasmussen Gabriel Condrea Li Yiwei

my %file_ext;
my %file_size;
my @temp;
my @extensions;
#check invalid oprand
my $numArgs = $#ARGV + 1;
unless ($numArgs == 0 || $numArgs == 1)
{
    print "USAGE: prog2.pl <size>\n";
    exit;
}

if ($numArgs == 1)
{
    if ($ARGV[0] eq "size"){
        #print "size\n";
    }
    else{
        print "USAGE: prog2.pl <size>\n";
        exit;
    }
}

#read the directory
opendir(D, ".");
my @dir_list = readdir(D);
closedir(D);

#remove any element beginning with .
my @new_list=();
foreach my $filename (@dir_list){
    unless ($filename =~ m/^\./) {
        push(@new_list,$filename);
    }	
}
#create a hash map for the extension
foreach my $file (@new_list){
    if($file =~ m/\./) {
        my $ext = ($file =~ m/([^.]+)$/)[0];
        $file_ext{ $file } = $ext;
    }
    else
    {
        $file_ext{ $file } = "no extension";
    }
}

#create a hash map for the size
@temp = %file_size;
foreach my $file (@new_list) {
    my $size = -s $file; 
    $file_size { $file } = $size;
}

#sort file array by extension
@temp = ();
foreach my $value (sort {$file_ext{$a} cmp $file_ext{$b}} keys %file_ext){
    push(@temp, $value);
}

#create array of extensions
my $last_ext = 0;
foreach my $file (@temp){
    my $ext = $file_ext{$file};
    unless ($ext eq $last_ext){
        push(@extensions, $ext);
    }
    $last_ext = $ext;
}

#push hash keys onto @temp array
@temp = ();
foreach my $key (keys(%file_ext)){
    push(@temp, $key);
}

#sort file array by name
@temp = sort { lc($a) cmp lc($b) } @temp;

#print files sorted by name and extension
#print "\n--printing out \@temp sorted alphabetically--\n";
foreach my $extension (@extensions){
    if ($numArgs == 0){
        print "\n===== $extension ======\n";
    }
    foreach my $file (@temp){
        if ($file_ext{$file} eq $extension){
            if ($numArgs == 0){
                print "$file $file_size{$file}\n";
            }
        }
    }
}

#sort file array by size
@temp = ();
foreach my $value (sort {$file_size{$a} <=> $file_size{$b}} keys %file_ext){
    push(@temp, $value);
}

#print files sorted by size and extension
foreach my $extension (@extensions){
    if ($numArgs == 1 && $ARGV[0] eq "size"){
        print "\n===== $extension ======\n";
    }
    foreach my $file (@temp){
        if ($file_ext{$file} eq $extension){
            if ($numArgs == 1 && $ARGV[0] eq "size"){
                print "$file $file_size{$file}\n";
            }
        }
    }
}
