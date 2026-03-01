/// Website Modules
import { Source } from '@/website/source';
import { Product } from '@/website/product';

/** Release Registry Details. */
export type Details = ReturnType<typeof Source.blog.getPage>;
export namespace Registry {
    //  PUBLIC METHODS  //

    /** Gets the current latest version url. */
    export const latest = () => `/blog/${Product.identifier}-v${Product.version}`;

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
