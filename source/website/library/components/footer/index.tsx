/// Vendor Modules
import clsx from 'clsx';
import React from 'react';

/** Footer Component. */
export interface Footer extends Footer.Props {}
export function Footer({ className, ...props }: Footer) {
    // prepare the classname to be used
    className = clsx(className, 'border-t flex items-center pt-5');

    // prepare the copyright as well
    const copyright = (
        <span key="copyright" className="text-sm ms-auto">
            Copyright &copy; {new Date().getFullYear()} Reuben Roessler
        </span>
    );

    // construct the resulting footer instance
    return <footer className={className} {...props} children={copyright} />;
}

export namespace Footer {
    //  TYPEDEFS  //

    /** Footer Component Properties. */
    export type Props = Omit<React.HTMLAttributes<HTMLElement>, 'children'>;
}
