/// Node Modules
import * as fs from 'node:fs';

/// Website Modules
import { Source } from '@/website/source';
import { Product } from '@/website/product';
import { Assets } from '@/website/assets';

/** Release Registry Details. */
export type Details = ReturnType<typeof Source.blog.getPage>;
export namespace Registry {
    //  PUBLIC METHODS  //

    /** Gets the current latest version url. */
    export const latest = () => {
        // get the current latest release
        const current = fs
            .readdirSync(Assets.blog())
            .filter((name) => name.startsWith(`${Product.identifier}-v`))
            .sort((a, b) => b.localeCompare(a))[0];

        // and resolve it as necessary now
        return `/blog/${current.substring(0, current.lastIndexOf('.'))}`;
    };

    /**
     * Gets a list of available release pages.
     * @param pages                 Pages to filter.
     */
    export const list = (pages = Source.blog.getPages()) =>
        pages.filter(validate).sort((a, b) => a.path.localeCompare(b.path));

    /**
     * Handles validating pages.
     * @param page                  Page to validate.
     */
    export const validate = (page?: NonNullable<Details>) => !!page?.data.title.startsWith(`${Product.shortName} v`);
}
